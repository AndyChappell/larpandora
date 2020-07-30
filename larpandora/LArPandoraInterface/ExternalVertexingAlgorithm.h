/**
 *  @file   larpandora/LArPandoraInterface/ExternalVertexingAlgorithm.h
 *
 *  @brief  Header file for algorithm creating Pandora vertices from externally generated Art vertices.
 *
 *  $Log: $
 */

#ifndef LAR_EXTERNAL_VERTEXING_ALGORITHM_H
#define LAR_EXTERNAL_VERTEXING_ALGORITHM_H 1

#include "Pandora/Algorithm.h"

namespace lar_pandora
{

/**
 *  @brief  ExternalVertexingAlgorithm class
 */
class ExternalVertexingAlgorithm : public pandora::Algorithm
{
public:
    /**
     *  @brief  Default constructor
     */
    ExternalVertexingAlgorithm();

    virtual ~ExternalVertexingAlgorithm() = default;

    /**
     *  @brief  Factory class for instantiating algorithm
     */
    class Factory : public pandora::AlgorithmFactory
    {
    public:
        pandora::Algorithm *CreateAlgorithm() const;
    };

private:
    pandora::StatusCode Run();
    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    std::string m_label;                        ///< The cluster module label to use
    std::string m_outputVertexListName;         ///< The output cluster list name
};

inline pandora::Algorithm *ExternalVertexingAlgorithm::Factory::CreateAlgorithm() const
{
    return new ExternalVertexingAlgorithm();
}

} // namespace lar_content

#endif // #ifndef LAR_EXTERNAL_VERTEXING_ALGORITHM_H

