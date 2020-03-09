/**
 *  @file   larpandora/LArPandoraInterface/TestInputAlgorithm.h
 *
 *  @brief  Header file for testing of Art IO.
 *
 *  $Log: $
 */

#ifndef LAR_TEST_INPUT_ALGORITHM_H
#define LAR_TEST_INPUT_ALGORITHM_H 1

#include "Pandora/Algorithm.h"

namespace lar_pandora
{

/**
 *  @brief  TestInputAlgorithm class
 */
class TestInputAlgorithm : public pandora::Algorithm
{
public:
    /**
     *  @brief  Default constructor
     */
    TestInputAlgorithm();

    virtual ~TestInputAlgorithm() = default;

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

    std::string m_hitfinderModuleLabel;     ///< The hitfinder module to use
};

inline pandora::Algorithm *TestInputAlgorithm::Factory::CreateAlgorithm() const
{
    return new TestInputAlgorithm();
}

} // namespace lar_content

#endif // #ifndef LAR_TEST_INPUT_ALGORITHM_H
