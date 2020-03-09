#include "larpandora/LArPandoraInterface/ArtIOMasterAlgorithm.h"

#include "Api/PandoraApi.h"
#include "larpandora/LArPandoraInterface/ArtIOContent.h"

#include <iostream>

using namespace pandora;

namespace lar_pandora
{

ArtIOMasterAlgorithm::ArtIOMasterAlgorithm()
{
}

StatusCode ArtIOMasterAlgorithm::RegisterCustomContent(const Pandora *const pPandora) const
{
    PANDORA_RETURN_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, ArtIOContent::RegisterAlgorithms(*pPandora));
    
    return STATUS_CODE_SUCCESS;
}

} // namespace lar_pandora

