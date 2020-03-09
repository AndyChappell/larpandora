/**
 *  @file   larpandora/LArPandoraInterface/TestOutputAlgorithm.cc
 *
 *  @brief  Header file for testing of Art IO.
 *
 *  $Log: $
 */

#include "larpandora/LArPandoraInterface/TestOutputAlgorithm.h"

#include "Pandora/AlgorithmHeaders.h"
#include "larpandora/LArPandoraInterface/LArArtIOWrapper.h"
#include "larpandora/LArPandoraInterface/LArPandora.h"
#include "larpandora/LArPandoraInterface/LArPandoraOutput.h"
#include "larpandoracontent/LArControlFlow/MultiPandoraApi.h"

using namespace pandora;

namespace lar_pandora
{

TestOutputAlgorithm::TestOutputAlgorithm() :
    m_instanceLabel{""}
{
}

pandora::StatusCode TestOutputAlgorithm::Run()
{
    const Pandora& pandora = this->GetPandora();
    const Pandora* primaryPandora = nullptr;
    try
    {
        primaryPandora = MultiPandoraApi::GetPrimaryPandoraInstance(&pandora);
    }
    catch(const StatusCodeException&)
    {   // This is the primary pandora instance
        primaryPandora = &this->GetPandora();
    }
    const LArArtIOWrapper* artIOWrapper = LArPandora::GetArtIOWrapper(primaryPandora);
    LArPandoraOutput::Settings settings{artIOWrapper->GetPandoraOutputSettings()}; 
    settings.m_instanceLabel = m_instanceLabel;
    if (settings.m_shouldProduceAllOutcomes)
    {
        LArPandoraOutput::ProduceArtOutput(settings.m_pPrimaryPandora, settings,
                artIOWrapper->GetIdToHitMap(), artIOWrapper->GetEvent());
    }
    settings.m_shouldProduceAllOutcomes = false;
    LArPandoraOutput::ProduceArtOutput(settings.m_pPrimaryPandora, settings,
            artIOWrapper->GetIdToHitMap(), artIOWrapper->GetEvent()); 

    return STATUS_CODE_SUCCESS;
}

pandora::StatusCode TestOutputAlgorithm::ReadSettings(const TiXmlHandle xmlHandle)
{
    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND,
            !=, XmlHelper::ReadValue(xmlHandle, "InstanceLabel", m_instanceLabel));

    return STATUS_CODE_SUCCESS;
}

} // namespace lar_pandora

