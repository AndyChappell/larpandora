/**
 *  @file   larpandora/LArPandoraInterface/LArArtIOWrapper.h
 *
 *  @brief  A wrapper for Art parameters required for input/output to/from Pandora
 */

#ifndef LAR_ART_IO_WRAPPER_H
#define LAR_ART_IO_WRAPPER_H 1

#include "larpandora/LArPandoraInterface/ILArPandora.h"
#include "larpandora/LArPandoraInterface/LArPandoraInput.h"
#include "larpandora/LArPandoraInterface/LArPandoraOutput.h"

namespace art { class Event; }

namespace lar_pandora
{

/**
 *  @brief  LArArtIOWrapper class
 */
class LArArtIOWrapper
{
public:
    /**
     *  @brief  Constructor
     *
     *  @param  inputSettings The Pandora input settings
     *  @param  outputSettings The Pandora output settings
     *  @param  idToHitMap The Art ID to hit map
     *  @param  driftVolumeMap The drift volume map
     *  @param  event The Art Event
     */
    LArArtIOWrapper(const LArPandoraInput::Settings& inputSettings, const LArPandoraOutput::Settings& outputSettings,
        IdToHitMap& idToHitMap, const LArDriftVolumeMap& driftVolumeMap, art::Event& event);

    /**
     *  @brief  Destructor
     */
    virtual ~LArArtIOWrapper();

    /**
     *  @brief  Return the Pandora input settings
     *
     *  @return The Pandora input settings
     */
    const LArPandoraInput::Settings& GetPandoraInputSettings() const;

    /**
     *  @brief  Return the Pandora output settings
     *
     *  @return The Pandora output settings
     */
    const LArPandoraOutput::Settings& GetPandoraOutputSettings() const;

    /**
     *  @brief  Return the map between the event ID and the hit map
     *
     *  @return The IdToHitMap
     */
    IdToHitMap& GetIdToHitMap() const;

    /**
     *  @brief  Return the drift volume for the event
     *
     *  @return The drift volume
     */
    const LArDriftVolumeMap& GetDriftVolumeMap() const;

    /**
     *  @brief  Return the art Event
     *
     *  @return The art Event
     */
    art::Event& GetEvent() const;

private:
    art::Event& m_event;
    IdToHitMap& m_idToHitMap;
    const LArDriftVolumeMap m_driftVolumeMap;
    const LArPandoraInput::Settings m_inputSettings;
    const LArPandoraOutput::Settings m_outputSettings;
};

//-----------------------------------------------------------------------------------------------------------------------------------------

inline const LArPandoraInput::Settings& LArArtIOWrapper::GetPandoraInputSettings() const
{
    return m_inputSettings;
}

//-----------------------------------------------------------------------------------------------------------------------------------------

inline const LArPandoraOutput::Settings& LArArtIOWrapper::GetPandoraOutputSettings() const
{
    return m_outputSettings;
}

//-----------------------------------------------------------------------------------------------------------------------------------------

inline IdToHitMap& LArArtIOWrapper::GetIdToHitMap() const
{
    return m_idToHitMap;
}

//-----------------------------------------------------------------------------------------------------------------------------------------

inline const LArDriftVolumeMap& LArArtIOWrapper::GetDriftVolumeMap() const
{
    return m_driftVolumeMap;
}

//-----------------------------------------------------------------------------------------------------------------------------------------

inline art::Event& LArArtIOWrapper::GetEvent() const
{
    return m_event;
}

}

#endif // LAR_ART_IO_WRAPPER_H

