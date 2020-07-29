/**
 *  @file   larpandora/ArtIOContent.cxx
 *
 *  @brief  Algorithm regsitration for Art IO content
 * 
 *  $Log: $
 */

#include "larpandora/LArPandoraInterface/ArtIOContent.h"

#include "Pandora/Pandora.h"
#include "Api/PandoraApi.h"

#include "larpandora/LArPandoraInterface/ExternalClusteringAlgorithm.h"
#include "larpandora/LArPandoraInterface/TestInputAlgorithm.h"
#include "larpandora/LArPandoraInterface/TestOutputAlgorithm.h"
#include "larpandora/LArPandoraInterface/ArtIOMasterAlgorithm.h"

using namespace pandora;

StatusCode ArtIOContent::RegisterAlgorithms(const Pandora &pandora)
{
    PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, PandoraApi::RegisterAlgorithmFactory(
                pandora, "ArtIOMaster", new lar_pandora::ArtIOMasterAlgorithm::Factory));

    PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, PandoraApi::RegisterAlgorithmFactory(
                pandora, "ExternalClustering", new lar_pandora::ExternalClusteringAlgorithm::Factory));

    PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, PandoraApi::RegisterAlgorithmFactory(
                pandora, "TestInput", new lar_pandora::TestInputAlgorithm::Factory));

    PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, PandoraApi::RegisterAlgorithmFactory(
                pandora, "TestOutput", new lar_pandora::TestOutputAlgorithm::Factory));

    return STATUS_CODE_SUCCESS;
}

