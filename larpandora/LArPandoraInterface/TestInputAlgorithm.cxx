/**
 *  @file   larpandora/LArPandoraInterface/TestInputAlgorithm.cc
 *
 *  @brief  Header file for testing of Art IO.
 *
 *  $Log: $
 */

#include "larpandora/LArPandoraInterface/TestInputAlgorithm.h"

#include "Pandora/AlgorithmHeaders.h"
#include "larpandora/LArPandoraInterface/LArArtIOWrapper.h"
#include "larpandora/LArPandoraInterface/LArPandora.h"
#include "larpandora/LArPandoraInterface/LArPandoraHelper.h"
#include "larpandora/LArPandoraInterface/LArPandoraInput.h"
#include "larpandoracontent/LArControlFlow/MultiPandoraApi.h"

using namespace pandora;

namespace lar_pandora
{

TestInputAlgorithm::TestInputAlgorithm() :
    m_hitfinderModuleLabel{""}
{
}

pandora::StatusCode TestInputAlgorithm::Run()
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
    LArPandoraInput::Settings settings{artIOWrapper->GetPandoraInputSettings()}; 

    HitVector artHits;
    LArPandoraHelper::CollectHits(artIOWrapper->GetEvent(), m_hitfinderModuleLabel, artHits);

    const CaloHitList *pCaloHitList{nullptr};
    PandoraContentApi::GetList(*this, "Input", pCaloHitList);
    std::cout << "The pre-existing input calo hit list " << pCaloHitList << " with length " << pCaloHitList->size() << std::endl;

    LArPandoraInput::CreatePandoraHits2D(settings, artIOWrapper->GetDriftVolumeMap(), artHits, artIOWrapper->GetIdToHitMap());

    PandoraContentApi::GetList(*this, "Input", pCaloHitList);
    std::cout << "The pre-existing input calo hit list " << pCaloHitList << " with length " << pCaloHitList->size() << std::endl;

    return STATUS_CODE_SUCCESS;
}

pandora::StatusCode TestInputAlgorithm::ReadSettings(const TiXmlHandle xmlHandle)
{
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::ReadValue(xmlHandle, "HitfinderModuleLabel", m_hitfinderModuleLabel));

    return STATUS_CODE_SUCCESS;
}

} // namespace lar_pandora

