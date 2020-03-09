/**
 *  @file   larpandora/LArPandoraInterface/ArtIOMasterAlgorithm.h
 *
 *  @brief  Header file for the Art IO master algorithm class.
 *
 *  $Log: $
 */
#ifndef LAR_ART_IO_MASTER_ALGORITHM_H
#define LAR_ART_IO_MASTER_ALGORITHM_H 1

#include "Pandora/Pandora.h"
#include "Pandora/PandoraInternal.h"
#include "Pandora/PandoraInputTypes.h"
#include "larpandoracontent/LArControlFlow/MasterAlgorithm.h"

namespace lar_pandora
{

/**
 *  @brief  MicroBooNEMasterAlgorithm class
 */
class ArtIOMasterAlgorithm : public lar_content::MasterAlgorithm
{
public:
    /**
     *  @brief  Default constructor
     */
    ArtIOMasterAlgorithm();

    /**
     *  @brief Destructor 
     */
    //~ArtIOMasterAlgorithm() = default;

    /**
     *  @brief  Factory class for instantiating algorithm
     */
    class Factory : public pandora::AlgorithmFactory
    {
    public:
        pandora::Algorithm *CreateAlgorithm() const;
    };


protected:
    pandora::StatusCode RegisterCustomContent(const pandora::Pandora *const pPandora) const;
};

inline pandora::Algorithm *ArtIOMasterAlgorithm::Factory::CreateAlgorithm() const
{
    return new ArtIOMasterAlgorithm();
}

} // namespace lar_pandora

#endif // #ifndef LAR_ART_IO_MASTER_ALGORITHM_H

