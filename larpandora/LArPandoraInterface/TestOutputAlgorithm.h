/**
 *  @file   larpandora/LArPandoraInterface/TestOutputAlgorithm.h
 *
 *  @brief  Header file for testing of Art IO.
 *
 *  $Log: $
 */

#ifndef LAR_TEST_OUTPUT_ALGORITHM_H
#define LAR_TEST_OUTPUT_ALGORITHM_H 1

#include "Pandora/Algorithm.h"

namespace lar_pandora
{

/**
 *  @brief  TestOutputAlgorithm class
 */
class TestOutputAlgorithm : public pandora::Algorithm
{
public:
    /**
     *  @brief  Default constructor
     */
    TestOutputAlgorithm();

    virtual ~TestOutputAlgorithm() = default;

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

    std::string m_instanceLabel;
};

inline pandora::Algorithm *TestOutputAlgorithm::Factory::CreateAlgorithm() const
{
    return new TestOutputAlgorithm();
}

} // namespace lar_content

#endif // #ifndef LAR_TEST_OUTPUT_ALGORITHM_H
