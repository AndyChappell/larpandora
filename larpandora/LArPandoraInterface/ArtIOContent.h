/**
 *  @file   larpandora/ArtIOContent.h
 *
 *  @brief  Header file detailing Art IO content
 * 
 *  $Log: $
 */
#ifndef LAR_ART_IO_CONTENT_H
#define LAR_ART_IO_CONTENT_H 1

#include "Pandora/Algorithm.h"

namespace pandora { class Pandora; }

/**
 *  @brief  ArtIOContent class
 */
class ArtIOContent
{
public:
    /**
     *  @brief  Register all the lar content algorithms and tools with pandora
     *
     *  @param  pandora the pandora instance with which to register content
     */
    static pandora::StatusCode RegisterAlgorithms(const pandora::Pandora &pandora);
};

#endif // #ifndef LAR_ART_IO_CONTENT_H

