/**
 *  @file   larpandora/LArPandoraInterface/ExternalVertexingAlgorithm.cc
 *
 *  @brief  Header file for algorithm creating Pandora vertices from externally generated Art vertices.
 *
 *  $Log: $
 */

#include "larpandora/LArPandoraInterface/ExternalVertexingAlgorithm.h"

#include "lardataobj/RecoBase/Vertex.h"

#include "Pandora/AlgorithmHeaders.h"
#include "larpandora/LArPandoraInterface/LArArtIOWrapper.h"
#include "larpandora/LArPandoraInterface/LArPandora.h"
#include "larpandora/LArPandoraInterface/LArPandoraInput.h"
#include "larpandoracontent/LArControlFlow/MultiPandoraApi.h"

using namespace pandora;

namespace lar_pandora
{

ExternalVertexingAlgorithm::ExternalVertexingAlgorithm() :
    m_label{""},
    m_outputVertexListName{""}
{
}

StatusCode ExternalVertexingAlgorithm::Run()
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

    art::Event &event{artIOWrapper->GetEvent()};
    try
    {
        // Create the Pandora vertices from the external Art vertices
        const VertexList *pVertexList{nullptr};
        std::string temporaryListName;
        PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::CreateTemporaryListAndSetCurrent(*this, pVertexList, temporaryListName));

        double xyz[3]{0., 0., 0.};
        auto artVertices{event.getValidHandle<std::vector<recob::Vertex>>(m_label)};
        for (const recob::Vertex &vertex : *artVertices)
        {
            vertex.XYZ(xyz);
            const CartesianVector position(static_cast<float>(xyz[0]), static_cast<float>(xyz[1]), static_cast<float>(xyz[2]));
            PandoraContentApi::Vertex::Parameters parameters;
            parameters.m_position = position;
            parameters.m_vertexLabel = VERTEX_INTERACTION;
            parameters.m_vertexType = VERTEX_3D;
            const Vertex *pVertex(nullptr);
            PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::Vertex::Create(*this, parameters, pVertex));
        }

        PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::SaveList<Vertex>(*this, temporaryListName, m_outputVertexListName));
        PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::ReplaceCurrentList<Vertex>(*this, m_outputVertexListName));
    }
    catch (...)
    {
        return STATUS_CODE_NOT_FOUND;
    }

    return STATUS_CODE_SUCCESS;
}

StatusCode ExternalVertexingAlgorithm::ReadSettings(const TiXmlHandle xmlHandle)
{
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::ReadValue(xmlHandle, "VertexModuleLabel", m_label));
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::ReadValue(xmlHandle, "OutputVertexListName", m_outputVertexListName));

    return STATUS_CODE_SUCCESS;
}

} // namespace lar_pandora

