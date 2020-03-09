#include "larpandora/LArPandoraInterface/LArArtIOWrapper.h"

using namespace lar_pandora;

LArArtIOWrapper::LArArtIOWrapper(const LArPandoraInput::Settings& inputSettings, const LArPandoraOutput::Settings& outputSettings,
    IdToHitMap& idToHitMap, const LArDriftVolumeMap& driftVolumeMap, art::Event& event) :
    m_event{event},
    m_idToHitMap{idToHitMap},
    m_driftVolumeMap{driftVolumeMap},
    m_inputSettings{inputSettings},
    m_outputSettings{outputSettings}
{
}

//-----------------------------------------------------------------------------------------------------------------------------------------

LArArtIOWrapper::~LArArtIOWrapper()
{
}

