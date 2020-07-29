/**
 *  @file   larpandora/LArPandoraInterface/ExternalClusteringAlgorithm.cc
 *
 *  @brief  Header file for testing of Art IO.
 *
 *  $Log: $
 */

#include "larpandora/LArPandoraInterface/ExternalClusteringAlgorithm.h"

#include "Pandora/AlgorithmHeaders.h"
#include "larpandora/LArPandoraInterface/LArArtIOWrapper.h"
#include "larpandora/LArPandoraInterface/LArPandora.h"
#include "larpandora/LArPandoraInterface/LArPandoraHelper.h"
#include "larpandora/LArPandoraInterface/LArPandoraInput.h"
#include "larpandoracontent/LArControlFlow/MultiPandoraApi.h"

using namespace pandora;

namespace lar_pandora
{

ExternalClusteringAlgorithm::ExternalClusteringAlgorithm() :
    m_label{""},
    m_outputClusterListName{""}
{
}

StatusCode ExternalClusteringAlgorithm::Run()
{
    const Pandora &pandora{this->GetPandora()};
    const Pandora *primaryPandora{nullptr};
    try
    {
        primaryPandora = MultiPandoraApi::GetPrimaryPandoraInstance(&pandora);
    }
    catch (const StatusCodeException&)
    {   // This is the primary pandora instance
        primaryPandora = &this->GetPandora();
    }
    const LArArtIOWrapper *artIOWrapper = LArPandora::GetArtIOWrapper(primaryPandora);
    const IdToHitMap &idToHitMap{artIOWrapper->GetIdToHitMap()};
    LArPandoraInput::Settings settings{artIOWrapper->GetPandoraInputSettings()}; 

    ClusterVector artClusters;
    ClustersToHits artClustersToHits;
    LArPandoraHelper::CollectClusters(artIOWrapper->GetEvent(), m_label, artClusters, artClustersToHits);

    if (artClusters.empty())
        return STATUS_CODE_SUCCESS;

    const CaloHitList *pCaloHitList{nullptr};
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::GetCurrentList(*this, pCaloHitList));
    std::map<const art::Ptr<recob::Hit>, const CaloHit*> artHitToCaloHitMap;
    for (const CaloHit *pCaloHit : *pCaloHitList)
    {
        // ATTN The CaloHit can come from the primary pandora instance (depth = 0) or one of its daughers (depth = 1).
        // Here we keep trying to access the ART hit increasing the depth step-by-step
        for (unsigned int depth = 0, maxDepth = 2; depth < maxDepth; ++depth)
        {
            // Navigate to the hit address in the pandora master instance (assuming the depth is correct)
            const pandora::CaloHit *pParentCaloHit{pCaloHit};
            for (unsigned int i = 0; i < depth; ++i)
                pParentCaloHit = static_cast<const pandora::CaloHit*>(pCaloHit->GetParentAddress());

            // Attempt to find the mapping from the "parent" calo hit to the ART hit
            const void *const pHitAddress(pParentCaloHit->GetParentAddress());
            const intptr_t hitID_temp((intptr_t) pHitAddress);
            const int hitID((int) hitID_temp);

            IdToHitMap::const_iterator artIter = idToHitMap.find(hitID);
            // If there is no such mapping from "parent" calo hit to the ART hit, then increase the depth and try again!
            if (artIter == idToHitMap.end())
                continue;
            
            artHitToCaloHitMap[artIter->second] = pCaloHit;
        }
    }

    // Cluster the Pandora CaloHits to match the clustering from the external Art hits
    std::string temporaryListName;
    const ClusterList *pClusterList{nullptr};
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::CreateTemporaryListAndSetCurrent(*this, pClusterList, temporaryListName));
    // Probably need to get the current list of pandora hits and access the art cluster/hit in a manner similar
    // to the way PandoraOutput does this
    for (const auto [ cluster, hits ] : artClustersToHits)
    {   (void) cluster;
        const Cluster *pCluster{nullptr};
        PandoraContentApi::Cluster::Parameters parameters;
        for (const art::Ptr<recob::Hit> hit : hits)
        {
            try
            {
                const CaloHit *pCaloHit{artHitToCaloHitMap.at(hit)};
                parameters.m_caloHitList.push_back(pCaloHit);
            }
            catch (...)
            {
                std::cout << "Warning: Found ART hit with no corresponding CaloHit" << std::endl;
            }
        }
        PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::Cluster::Create(*this, parameters, pCluster));
    }
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::SaveList<Cluster>(*this, temporaryListName, m_outputClusterListName));
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::ReplaceCurrentList<Cluster>(*this, m_outputClusterListName));

    return STATUS_CODE_SUCCESS;
}

StatusCode ExternalClusteringAlgorithm::ReadSettings(const TiXmlHandle xmlHandle)
{
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::ReadValue(xmlHandle, "ClusterModuleLabel", m_label));
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::ReadValue(xmlHandle, "OutputClusterListName", m_outputClusterListName));

    return STATUS_CODE_SUCCESS;
}

} // namespace lar_pandora

