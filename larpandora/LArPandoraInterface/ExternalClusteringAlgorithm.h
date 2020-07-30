/**
 *  @file   larpandora/LArPandoraInterface/ExternalClusteringAlgorithm.h
 *
 *  @brief  Header file for algorithm creating Pandora clusters from externally generated Art clusters.
 *
 *  $Log: $
 */

#ifndef LAR_EXTERNAL_CLUSTERING_ALGORITHM_H
#define LAR_EXTERNAL_CLUSTERING_ALGORITHM_H 1

#include "Pandora/Algorithm.h"

namespace lar_pandora
{

/**
 *  @brief  ExternalClusteringAlgorithm class
 */
class ExternalClusteringAlgorithm : public pandora::Algorithm
{
public:
    /**
     *  @brief  Default constructor
     */
    ExternalClusteringAlgorithm();

    virtual ~ExternalClusteringAlgorithm() = default;

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
    std::string m_outputClusterListName;        ///< The output cluster list name
};

inline pandora::Algorithm *ExternalClusteringAlgorithm::Factory::CreateAlgorithm() const
{
    return new ExternalClusteringAlgorithm();
}

} // namespace lar_content

#endif // #ifndef LAR_EXTERNAL_CLUSTERING_ALGORITHM_H
