// Generated automatically from 'IUserSettings.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_UserSettings.h"
#include <interfaces/IUserSettings.h>

namespace WPEFramework {

namespace Exchange {

    namespace JUserSettings {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IUserSettings* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JUserSettings"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'setAudioDescription' - Sets AudioDescription ON/OFF
            _module_.Register<JsonData::UserSettings::SetAudioDescriptionParamsInfo, void>(_T("setAudioDescription"), 
                [_impl_](const JsonData::UserSettings::SetAudioDescriptionParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _enabled{params.Enabled};

                    _errorCode = _impl_->SetAudioDescription(_enabled);

                    return (_errorCode);
                });

            // Method: 'getAudioDescription' - Gets the current AudioDescription setting
            _module_.Register<void, Core::JSON::Boolean>(_T("getAudioDescription"), 
                [_impl_](Core::JSON::Boolean& enabled) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    bool _enabled{};

                    _errorCode = _impl_->GetAudioDescription(_enabled);

                    if (_errorCode == Core::ERROR_NONE) {
                        enabled = _enabled;
                    }

                    return (_errorCode);
                });

            // Method: 'setPreferredAudioLanguages' - A prioritized list of ISO 639-2/B codes for the preferred audio languages,
                    //  expressed as a comma separated lists of languages of zero of more elements
            _module_.Register<JsonData::UserSettings::SetPreferredAudioLanguagesParamsInfo, void>(_T("setPreferredAudioLanguages"), 
                [_impl_](const JsonData::UserSettings::SetPreferredAudioLanguagesParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _preferredLanguages{params.PreferredLanguages};

                    _errorCode = _impl_->SetPreferredAudioLanguages(_preferredLanguages);

                    return (_errorCode);
                });

            // Method: 'getPreferredAudioLanguages' - Gets the current PreferredAudioLanguages setting
            _module_.Register<void, Core::JSON::String>(_T("getPreferredAudioLanguages"), 
                [_impl_](Core::JSON::String& preferredLanguages) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _preferredLanguages{};

                    _errorCode = _impl_->GetPreferredAudioLanguages(_preferredLanguages);

                    if (_errorCode == Core::ERROR_NONE) {
                        preferredLanguages = _preferredLanguages;
                    }

                    return (_errorCode);
                });

            // Method: 'setPresentationLanguage' - Sets the presentationLanguage in a full BCP 47 value, including script, region, variant
            _module_.Register<JsonData::UserSettings::SetPresentationLanguageParamsInfo, void>(_T("setPresentationLanguage"), 
                [_impl_](const JsonData::UserSettings::SetPresentationLanguageParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _presentationLanguage{params.PresentationLanguage};

                    _errorCode = _impl_->SetPresentationLanguage(_presentationLanguage);

                    return (_errorCode);
                });

            // Method: 'getPresentationLanguage' - Gets the presentationLanguage
            _module_.Register<void, Core::JSON::String>(_T("getPresentationLanguage"), 
                [_impl_](Core::JSON::String& presentationLanguage) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _presentationLanguage{};

                    _errorCode = _impl_->GetPresentationLanguage(_presentationLanguage);

                    if (_errorCode == Core::ERROR_NONE) {
                        presentationLanguage = _presentationLanguage;
                    }

                    return (_errorCode);
                });

            // Method: 'setCaptions' - brief Sets Captions ON/OFF
            _module_.Register<JsonData::UserSettings::SetAudioDescriptionParamsInfo, void>(_T("setCaptions"), 
                [_impl_](const JsonData::UserSettings::SetAudioDescriptionParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _enabled{params.Enabled};

                    _errorCode = _impl_->SetCaptions(_enabled);

                    return (_errorCode);
                });

            // Method: 'getCaptions' - Gets the Captions setting
            _module_.Register<void, Core::JSON::Boolean>(_T("getCaptions"), 
                [_impl_](Core::JSON::Boolean& enabled) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    bool _enabled{};

                    _errorCode = _impl_->GetCaptions(_enabled);

                    if (_errorCode == Core::ERROR_NONE) {
                        enabled = _enabled;
                    }

                    return (_errorCode);
                });

            // Method: 'setPreferredCaptionsLanguages' - Set preferred languages for captions
            _module_.Register<JsonData::UserSettings::SetPreferredAudioLanguagesParamsInfo, void>(_T("setPreferredCaptionsLanguages"), 
                [_impl_](const JsonData::UserSettings::SetPreferredAudioLanguagesParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _preferredLanguages{params.PreferredLanguages};

                    _errorCode = _impl_->SetPreferredCaptionsLanguages(_preferredLanguages);

                    return (_errorCode);
                });

            // Method: 'getPreferredCaptionsLanguages' - Gets the current PreferredCaptionsLanguages setting
            _module_.Register<void, Core::JSON::String>(_T("getPreferredCaptionsLanguages"), 
                [_impl_](Core::JSON::String& preferredLanguages) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _preferredLanguages{};

                    _errorCode = _impl_->GetPreferredCaptionsLanguages(_preferredLanguages);

                    if (_errorCode == Core::ERROR_NONE) {
                        preferredLanguages = _preferredLanguages;
                    }

                    return (_errorCode);
                });

            // Method: 'setPreferredClosedCaptionService' - Sets the PreferredClosedCaptionService
            _module_.Register<JsonData::UserSettings::SetPreferredClosedCaptionServiceParamsInfo, void>(_T("setPreferredClosedCaptionService"), 
                [_impl_](const JsonData::UserSettings::SetPreferredClosedCaptionServiceParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _service{params.Service};

                    _errorCode = _impl_->SetPreferredClosedCaptionService(_service);

                    return (_errorCode);
                });

            // Method: 'getPreferredClosedCaptionService' - Gets the current PreferredClosedCaptionService setting
            _module_.Register<void, Core::JSON::String>(_T("getPreferredClosedCaptionService"), 
                [_impl_](Core::JSON::String& service) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _service{};

                    _errorCode = _impl_->GetPreferredClosedCaptionService(_service);

                    if (_errorCode == Core::ERROR_NONE) {
                        service = _service;
                    }

                    return (_errorCode);
                });

            // Method: 'setPrivacyMode' - Sets the PrivacyMode
            _module_.Register<JsonData::UserSettings::SetPrivacyModeParamsInfo, void>(_T("setPrivacyMode"), 
                [_impl_](const JsonData::UserSettings::SetPrivacyModeParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _privacyMode{params.PrivacyMode};

                    _errorCode = _impl_->SetPrivacyMode(_privacyMode);

                    return (_errorCode);
                });

            // Method: 'getPrivacyMode' - Gets the current PrivacyMode setting
            _module_.Register<void, Core::JSON::String>(_T("getPrivacyMode"), 
                [_impl_](Core::JSON::String& privacyMode) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _privacyMode{};

                    _errorCode = _impl_->GetPrivacyMode(_privacyMode);

                    if (_errorCode == Core::ERROR_NONE) {
                        privacyMode = _privacyMode;
                    }

                    return (_errorCode);
                });

            // Method: 'SetPinControl' - Sets PinControl ON/OFF
            _module_.Register<JsonData::UserSettings::SetPinControlParamsInfo, void>(_T("SetPinControl"), 
                [_impl_](const JsonData::UserSettings::SetPinControlParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _pinControl{params.PinControl};

                    _errorCode = _impl_->SetPinControl(_pinControl);

                    return (_errorCode);
                });

            // Method: 'setPinControl' - Sets PinControl ON/OFF
            _module_.Register<JsonData::UserSettings::SetPinControlParamsInfo, void>(_T("setPinControl"), 
                [_impl_](const JsonData::UserSettings::SetPinControlParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _pinControl{params.PinControl};

                    _errorCode = _impl_->SetPinControl(_pinControl);

                    return (_errorCode);
                });

            // Method: 'getPinControl' - Gets the PinControl setting
            _module_.Register<void, Core::JSON::Boolean>(_T("getPinControl"), 
                [_impl_](Core::JSON::Boolean& pinControl) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    bool _pinControl{};

                    _errorCode = _impl_->GetPinControl(_pinControl);

                    if (_errorCode == Core::ERROR_NONE) {
                        pinControl = _pinControl;
                    }

                    return (_errorCode);
                });

            // Method: 'setViewingRestrictions' - Sets the ViewingRestrictions
            _module_.Register<JsonData::UserSettings::SetViewingRestrictionsParamsInfo, void>(_T("setViewingRestrictions"), 
                [_impl_](const JsonData::UserSettings::SetViewingRestrictionsParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _viewingRestrictions{params.ViewingRestrictions};

                    _errorCode = _impl_->SetViewingRestrictions(_viewingRestrictions);

                    return (_errorCode);
                });

            // Method: 'getViewingRestrictions' - Gets the current ViewingRestrictions
            _module_.Register<void, Core::JSON::String>(_T("getViewingRestrictions"), 
                [_impl_](Core::JSON::String& viewingRestrictions) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _viewingRestrictions{};

                    _errorCode = _impl_->GetViewingRestrictions(_viewingRestrictions);

                    if (_errorCode == Core::ERROR_NONE) {
                        viewingRestrictions = _viewingRestrictions;
                    }

                    return (_errorCode);
                });

            // Method: 'setViewingRestrictionsWindow' - Sets the ViewingRestrictionsWindow
            _module_.Register<JsonData::UserSettings::SetViewingRestrictionsWindowParamsInfo, void>(_T("setViewingRestrictionsWindow"), 
                [_impl_](const JsonData::UserSettings::SetViewingRestrictionsWindowParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _viewingRestrictionsWindow{params.ViewingRestrictionsWindow};

                    _errorCode = _impl_->SetViewingRestrictionsWindow(_viewingRestrictionsWindow);

                    return (_errorCode);
                });

            // Method: 'getViewingRestrictionsWindow' - Gets the current ViewingRestrictionsWindow
            _module_.Register<void, Core::JSON::String>(_T("getViewingRestrictionsWindow"), 
                [_impl_](Core::JSON::String& viewingRestrictionsWindow) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _viewingRestrictionsWindow{};

                    _errorCode = _impl_->GetViewingRestrictionsWindow(_viewingRestrictionsWindow);

                    if (_errorCode == Core::ERROR_NONE) {
                        viewingRestrictionsWindow = _viewingRestrictionsWindow;
                    }

                    return (_errorCode);
                });

            // Method: 'setLiveWatershed' - Sets LiveWatershed ON/OFF
            _module_.Register<JsonData::UserSettings::SetLiveWatershedParamsInfo, void>(_T("setLiveWatershed"), 
                [_impl_](const JsonData::UserSettings::SetLiveWatershedParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _liveWatershed{params.LiveWatershed};

                    _errorCode = _impl_->SetLiveWatershed(_liveWatershed);

                    return (_errorCode);
                });

            // Method: 'getLiveWatershed' - Gets the LiveWatershed setting
            _module_.Register<void, Core::JSON::Boolean>(_T("getLiveWatershed"), 
                [_impl_](Core::JSON::Boolean& liveWatershed) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    bool _liveWatershed{};

                    _errorCode = _impl_->GetLiveWatershed(_liveWatershed);

                    if (_errorCode == Core::ERROR_NONE) {
                        liveWatershed = _liveWatershed;
                    }

                    return (_errorCode);
                });

            // Method: 'setPlaybackWatershed' - Sets PlaybackWatershed ON/OFF
            _module_.Register<JsonData::UserSettings::SetPlaybackWatershedParamsInfo, void>(_T("setPlaybackWatershed"), 
                [_impl_](const JsonData::UserSettings::SetPlaybackWatershedParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _playbackWatershed{params.PlaybackWatershed};

                    _errorCode = _impl_->SetPlaybackWatershed(_playbackWatershed);

                    return (_errorCode);
                });

            // Method: 'getPlaybackWatershed' - Gets the PlaybackWatershed setting
            _module_.Register<void, Core::JSON::Boolean>(_T("getPlaybackWatershed"), 
                [_impl_](Core::JSON::Boolean& playbackWatershed) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    bool _playbackWatershed{};

                    _errorCode = _impl_->GetPlaybackWatershed(_playbackWatershed);

                    if (_errorCode == Core::ERROR_NONE) {
                        playbackWatershed = _playbackWatershed;
                    }

                    return (_errorCode);
                });

            // Method: 'setBlockNotRatedContent' - Sets BlockNotRatedContent ON/OFF
            _module_.Register<JsonData::UserSettings::SetBlockNotRatedContentParamsInfo, void>(_T("setBlockNotRatedContent"), 
                [_impl_](const JsonData::UserSettings::SetBlockNotRatedContentParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _blockNotRatedContent{params.BlockNotRatedContent};

                    _errorCode = _impl_->SetBlockNotRatedContent(_blockNotRatedContent);

                    return (_errorCode);
                });

            // Method: 'getBlockNotRatedContent' - Gets the BlockNotRatedContent setting
            _module_.Register<void, Core::JSON::Boolean>(_T("getBlockNotRatedContent"), 
                [_impl_](Core::JSON::Boolean& blockNotRatedContent) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    bool _blockNotRatedContent{};

                    _errorCode = _impl_->GetBlockNotRatedContent(_blockNotRatedContent);

                    if (_errorCode == Core::ERROR_NONE) {
                        blockNotRatedContent = _blockNotRatedContent;
                    }

                    return (_errorCode);
                });

            // Method: 'setPinOnPurchase' - Sets PinOnPurchase ON/OFF
            _module_.Register<JsonData::UserSettings::SetPinOnPurchaseParamsInfo, void>(_T("setPinOnPurchase"), 
                [_impl_](const JsonData::UserSettings::SetPinOnPurchaseParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _pinOnPurchase{params.PinOnPurchase};

                    _errorCode = _impl_->SetPinOnPurchase(_pinOnPurchase);

                    return (_errorCode);
                });

            // Method: 'getPinOnPurchase' - Gets the PinOnPurchase setting
            _module_.Register<void, Core::JSON::Boolean>(_T("getPinOnPurchase"), 
                [_impl_](Core::JSON::Boolean& pinOnPurchase) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    bool _pinOnPurchase{};

                    _errorCode = _impl_->GetPinOnPurchase(_pinOnPurchase);

                    if (_errorCode == Core::ERROR_NONE) {
                        pinOnPurchase = _pinOnPurchase;
                    }

                    return (_errorCode);
                });

            // Method: 'setHighContrast' - Sets highContrast
            _module_.Register<JsonData::UserSettings::SetAudioDescriptionParamsInfo, void>(_T("setHighContrast"), 
                [_impl_](const JsonData::UserSettings::SetAudioDescriptionParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _enabled{params.Enabled};

                    _errorCode = _impl_->SetHighContrast(_enabled);

                    return (_errorCode);
                });

            // Method: 'getHighContrast' - Gets the current highContrast setting
            _module_.Register<void, Core::JSON::Boolean>(_T("getHighContrast"), 
                [_impl_](Core::JSON::Boolean& enabled) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    bool _enabled{};

                    _errorCode = _impl_->GetHighContrast(_enabled);

                    if (_errorCode == Core::ERROR_NONE) {
                        enabled = _enabled;
                    }

                    return (_errorCode);
                });

            // Method: 'setVoiceGuidance' - Sets voiceGuidance
            _module_.Register<JsonData::UserSettings::SetAudioDescriptionParamsInfo, void>(_T("setVoiceGuidance"), 
                [_impl_](const JsonData::UserSettings::SetAudioDescriptionParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _enabled{params.Enabled};

                    _errorCode = _impl_->SetVoiceGuidance(_enabled);

                    return (_errorCode);
                });

            // Method: 'getVoiceGuidance' - Gets the current voiceGuidance setting
            _module_.Register<void, Core::JSON::Boolean>(_T("getVoiceGuidance"), 
                [_impl_](Core::JSON::Boolean& enabled) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    bool _enabled{};

                    _errorCode = _impl_->GetVoiceGuidance(_enabled);

                    if (_errorCode == Core::ERROR_NONE) {
                        enabled = _enabled;
                    }

                    return (_errorCode);
                });

            // Method: 'setVoiceGuidanceRate' - Sets voiceGuidanceRate
            _module_.Register<JsonData::UserSettings::SetVoiceGuidanceRateParamsInfo, void>(_T("setVoiceGuidanceRate"), 
                [_impl_](const JsonData::UserSettings::SetVoiceGuidanceRateParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const double _rate{params.Rate};

                    _errorCode = _impl_->SetVoiceGuidanceRate(_rate);

                    return (_errorCode);
                });

            // Method: 'getVoiceGuidanceRate' - Gets the current voiceGuidanceRate setting
            _module_.Register<void, Core::JSON::Double>(_T("getVoiceGuidanceRate"), 
                [_impl_](Core::JSON::Double& rate) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    double _rate{};

                    _errorCode = _impl_->GetVoiceGuidanceRate(_rate);

                    if (_errorCode == Core::ERROR_NONE) {
                        rate = _rate;
                    }

                    return (_errorCode);
                });

            // Method: 'setVoiceGuidanceHints' - Sets voiceGuidanceHints ON/OFF
            _module_.Register<JsonData::UserSettings::SetVoiceGuidanceHintsParamsInfo, void>(_T("setVoiceGuidanceHints"), 
                [_impl_](const JsonData::UserSettings::SetVoiceGuidanceHintsParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _hints{params.Hints};

                    _errorCode = _impl_->SetVoiceGuidanceHints(_hints);

                    return (_errorCode);
                });

            // Method: 'getVoiceGuidanceHints' - Gets the current voiceGuidanceHints setting
            _module_.Register<void, Core::JSON::Boolean>(_T("getVoiceGuidanceHints"), 
                [_impl_](Core::JSON::Boolean& hints) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    bool _hints{};

                    _errorCode = _impl_->GetVoiceGuidanceHints(_hints);

                    if (_errorCode == Core::ERROR_NONE) {
                        hints = _hints;
                    }

                    return (_errorCode);
                });

            // Method: 'setContentPin' - Sets the ContentPin
            _module_.Register<JsonData::UserSettings::SetContentPinParamsInfo, void>(_T("setContentPin"), 
                [_impl_](const JsonData::UserSettings::SetContentPinParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _contentPin{params.ContentPin};

                    _errorCode = _impl_->SetContentPin(_contentPin);

                    return (_errorCode);
                });

            // Method: 'getContentPin' - Gets the ContentPin
            _module_.Register<void, Core::JSON::String>(_T("getContentPin"), 
                [_impl_](Core::JSON::String& contentPin) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _contentPin{};

                    _errorCode = _impl_->GetContentPin(_contentPin);

                    if (_errorCode == Core::ERROR_NONE) {
                        contentPin = _contentPin;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("setAudioDescription"));
            _module_.Unregister(_T("getAudioDescription"));
            _module_.Unregister(_T("setPreferredAudioLanguages"));
            _module_.Unregister(_T("getPreferredAudioLanguages"));
            _module_.Unregister(_T("setPresentationLanguage"));
            _module_.Unregister(_T("getPresentationLanguage"));
            _module_.Unregister(_T("setCaptions"));
            _module_.Unregister(_T("getCaptions"));
            _module_.Unregister(_T("setPreferredCaptionsLanguages"));
            _module_.Unregister(_T("getPreferredCaptionsLanguages"));
            _module_.Unregister(_T("setPreferredClosedCaptionService"));
            _module_.Unregister(_T("getPreferredClosedCaptionService"));
            _module_.Unregister(_T("setPrivacyMode"));
            _module_.Unregister(_T("getPrivacyMode"));
            _module_.Unregister(_T("SetPinControl"));
            _module_.Unregister(_T("setPinControl"));
            _module_.Unregister(_T("getPinControl"));
            _module_.Unregister(_T("setViewingRestrictions"));
            _module_.Unregister(_T("getViewingRestrictions"));
            _module_.Unregister(_T("setViewingRestrictionsWindow"));
            _module_.Unregister(_T("getViewingRestrictionsWindow"));
            _module_.Unregister(_T("setLiveWatershed"));
            _module_.Unregister(_T("getLiveWatershed"));
            _module_.Unregister(_T("setPlaybackWatershed"));
            _module_.Unregister(_T("getPlaybackWatershed"));
            _module_.Unregister(_T("setBlockNotRatedContent"));
            _module_.Unregister(_T("getBlockNotRatedContent"));
            _module_.Unregister(_T("setPinOnPurchase"));
            _module_.Unregister(_T("getPinOnPurchase"));
            _module_.Unregister(_T("setHighContrast"));
            _module_.Unregister(_T("getHighContrast"));
            _module_.Unregister(_T("setVoiceGuidance"));
            _module_.Unregister(_T("getVoiceGuidance"));
            _module_.Unregister(_T("setVoiceGuidanceRate"));
            _module_.Unregister(_T("getVoiceGuidanceRate"));
            _module_.Unregister(_T("setVoiceGuidanceHints"));
            _module_.Unregister(_T("getVoiceGuidanceHints"));
            _module_.Unregister(_T("setContentPin"));
            _module_.Unregister(_T("getContentPin"));
        }

        namespace Event {

            // Event: 'onAudioDescriptionChanged' - The AudioDescription setting has changed
            static void OnAudioDescriptionChanged(const JSONRPC& _module_, const JsonData::UserSettings::SetAudioDescriptionParamsInfo& params)
            {
                _module_.Notify(_T("onAudioDescriptionChanged"), params);
            }

            // Event: 'onAudioDescriptionChanged' - The AudioDescription setting has changed
            static void OnAudioDescriptionChanged(const JSONRPC& _module_, const Core::JSON::Boolean& enabled)
            {
                JsonData::UserSettings::SetAudioDescriptionParamsInfo _params_;
                _params_.Enabled = enabled;

                OnAudioDescriptionChanged(_module_, _params_);
            }

            // Event: 'onAudioDescriptionChanged' - The AudioDescription setting has changed
            static void OnAudioDescriptionChanged(const JSONRPC& _module_, const bool& enabled)
            {
                JsonData::UserSettings::SetAudioDescriptionParamsInfo _params_;
                _params_.Enabled = enabled;

                OnAudioDescriptionChanged(_module_, _params_);
            }

            // Event: 'onPreferredAudioLanguagesChanged' - The preferredLanguages setting has changed
            static void OnPreferredAudioLanguagesChanged(const JSONRPC& _module_, const JsonData::UserSettings::SetPreferredAudioLanguagesParamsInfo& params)
            {
                _module_.Notify(_T("onPreferredAudioLanguagesChanged"), params);
            }

            // Event: 'onPreferredAudioLanguagesChanged' - The preferredLanguages setting has changed
            static void OnPreferredAudioLanguagesChanged(const JSONRPC& _module_, const Core::JSON::String& preferredLanguages)
            {
                JsonData::UserSettings::SetPreferredAudioLanguagesParamsInfo _params_;
                _params_.PreferredLanguages = preferredLanguages;

                OnPreferredAudioLanguagesChanged(_module_, _params_);
            }

            // Event: 'onPreferredAudioLanguagesChanged' - The preferredLanguages setting has changed
            static void OnPreferredAudioLanguagesChanged(const JSONRPC& _module_, const string& preferredLanguages)
            {
                JsonData::UserSettings::SetPreferredAudioLanguagesParamsInfo _params_;
                _params_.PreferredLanguages = preferredLanguages;

                OnPreferredAudioLanguagesChanged(_module_, _params_);
            }

            // Event: 'onPresentationLanguageChanged' - The PresentationLanguages setting has changed
            static void OnPresentationLanguageChanged(const JSONRPC& _module_, const JsonData::UserSettings::SetPresentationLanguageParamsInfo& params)
            {
                _module_.Notify(_T("onPresentationLanguageChanged"), params);
            }

            // Event: 'onPresentationLanguageChanged' - The PresentationLanguages setting has changed
            static void OnPresentationLanguageChanged(const JSONRPC& _module_, const Core::JSON::String& presentationLanguage)
            {
                JsonData::UserSettings::SetPresentationLanguageParamsInfo _params_;
                _params_.PresentationLanguage = presentationLanguage;

                OnPresentationLanguageChanged(_module_, _params_);
            }

            // Event: 'onPresentationLanguageChanged' - The PresentationLanguages setting has changed
            static void OnPresentationLanguageChanged(const JSONRPC& _module_, const string& presentationLanguage)
            {
                JsonData::UserSettings::SetPresentationLanguageParamsInfo _params_;
                _params_.PresentationLanguage = presentationLanguage;

                OnPresentationLanguageChanged(_module_, _params_);
            }

            // Event: 'onCaptionsChanged' - The Captions setting has changed
            static void OnCaptionsChanged(const JSONRPC& _module_, const JsonData::UserSettings::SetAudioDescriptionParamsInfo& params)
            {
                _module_.Notify(_T("onCaptionsChanged"), params);
            }

            // Event: 'onCaptionsChanged' - The Captions setting has changed
            static void OnCaptionsChanged(const JSONRPC& _module_, const Core::JSON::Boolean& enabled)
            {
                JsonData::UserSettings::SetAudioDescriptionParamsInfo _params_;
                _params_.Enabled = enabled;

                OnCaptionsChanged(_module_, _params_);
            }

            // Event: 'onCaptionsChanged' - The Captions setting has changed
            static void OnCaptionsChanged(const JSONRPC& _module_, const bool& enabled)
            {
                JsonData::UserSettings::SetAudioDescriptionParamsInfo _params_;
                _params_.Enabled = enabled;

                OnCaptionsChanged(_module_, _params_);
            }

            // Event: 'onPreferredCaptionsLanguagesChanged' - The PreferredCaptionsLanguages setting has changed
            static void OnPreferredCaptionsLanguagesChanged(const JSONRPC& _module_, const JsonData::UserSettings::SetPreferredAudioLanguagesParamsInfo& params)
            {
                _module_.Notify(_T("onPreferredCaptionsLanguagesChanged"), params);
            }

            // Event: 'onPreferredCaptionsLanguagesChanged' - The PreferredCaptionsLanguages setting has changed
            static void OnPreferredCaptionsLanguagesChanged(const JSONRPC& _module_, const Core::JSON::String& preferredLanguages)
            {
                JsonData::UserSettings::SetPreferredAudioLanguagesParamsInfo _params_;
                _params_.PreferredLanguages = preferredLanguages;

                OnPreferredCaptionsLanguagesChanged(_module_, _params_);
            }

            // Event: 'onPreferredCaptionsLanguagesChanged' - The PreferredCaptionsLanguages setting has changed
            static void OnPreferredCaptionsLanguagesChanged(const JSONRPC& _module_, const string& preferredLanguages)
            {
                JsonData::UserSettings::SetPreferredAudioLanguagesParamsInfo _params_;
                _params_.PreferredLanguages = preferredLanguages;

                OnPreferredCaptionsLanguagesChanged(_module_, _params_);
            }

            // Event: 'onPreferredClosedCaptionServiceChanged' - The PreferredClosedCaptionService setting has changed
            static void OnPreferredClosedCaptionServiceChanged(const JSONRPC& _module_,
                     const JsonData::UserSettings::SetPreferredClosedCaptionServiceParamsInfo& params)
            {
                _module_.Notify(_T("onPreferredClosedCaptionServiceChanged"), params);
            }

            // Event: 'onPreferredClosedCaptionServiceChanged' - The PreferredClosedCaptionService setting has changed
            static void OnPreferredClosedCaptionServiceChanged(const JSONRPC& _module_, const Core::JSON::String& service)
            {
                JsonData::UserSettings::SetPreferredClosedCaptionServiceParamsInfo _params_;
                _params_.Service = service;

                OnPreferredClosedCaptionServiceChanged(_module_, _params_);
            }

            // Event: 'onPreferredClosedCaptionServiceChanged' - The PreferredClosedCaptionService setting has changed
            static void OnPreferredClosedCaptionServiceChanged(const JSONRPC& _module_, const string& service)
            {
                JsonData::UserSettings::SetPreferredClosedCaptionServiceParamsInfo _params_;
                _params_.Service = service;

                OnPreferredClosedCaptionServiceChanged(_module_, _params_);
            }

            // Event: 'onPrivacyModeChanged' - The PrivacyMode setting has changed
            static void OnPrivacyModeChanged(const JSONRPC& _module_, const JsonData::UserSettings::SetPrivacyModeParamsInfo& params)
            {
                _module_.Notify(_T("onPrivacyModeChanged"), params);
            }

            // Event: 'onPrivacyModeChanged' - The PrivacyMode setting has changed
            static void OnPrivacyModeChanged(const JSONRPC& _module_, const Core::JSON::String& privacyMode)
            {
                JsonData::UserSettings::SetPrivacyModeParamsInfo _params_;
                _params_.PrivacyMode = privacyMode;

                OnPrivacyModeChanged(_module_, _params_);
            }

            // Event: 'onPrivacyModeChanged' - The PrivacyMode setting has changed
            static void OnPrivacyModeChanged(const JSONRPC& _module_, const string& privacyMode)
            {
                JsonData::UserSettings::SetPrivacyModeParamsInfo _params_;
                _params_.PrivacyMode = privacyMode;

                OnPrivacyModeChanged(_module_, _params_);
            }

            // Event: 'OnPinControlChanged' - The PinControl setting has changed
            static void OnPinControlChanged(const JSONRPC& _module_, const JsonData::UserSettings::SetPinControlParamsInfo& params)
            {
                _module_.Notify(_T("OnPinControlChanged"), params);
                _module_.Notify(_T("onPinControlChanged"), params);
            }

            // Event: 'OnPinControlChanged' - The PinControl setting has changed
            static void OnPinControlChanged(const JSONRPC& _module_, const Core::JSON::Boolean& pinControl)
            {
                JsonData::UserSettings::SetPinControlParamsInfo _params_;
                _params_.PinControl = pinControl;

                OnPinControlChanged(_module_, _params_);
            }

            // Event: 'OnPinControlChanged' - The PinControl setting has changed
            static void OnPinControlChanged(const JSONRPC& _module_, const bool& pinControl)
            {
                JsonData::UserSettings::SetPinControlParamsInfo _params_;
                _params_.PinControl = pinControl;

                OnPinControlChanged(_module_, _params_);
            }

            // Event: 'onViewingRestrictionsChanged' - The ViewingRestrictions setting has changed
            static void OnViewingRestrictionsChanged(const JSONRPC& _module_, const JsonData::UserSettings::SetViewingRestrictionsParamsInfo& params)
            {
                _module_.Notify(_T("onViewingRestrictionsChanged"), params);
            }

            // Event: 'onViewingRestrictionsChanged' - The ViewingRestrictions setting has changed
            static void OnViewingRestrictionsChanged(const JSONRPC& _module_, const Core::JSON::String& viewingRestrictions)
            {
                JsonData::UserSettings::SetViewingRestrictionsParamsInfo _params_;
                _params_.ViewingRestrictions = viewingRestrictions;

                OnViewingRestrictionsChanged(_module_, _params_);
            }

            // Event: 'onViewingRestrictionsChanged' - The ViewingRestrictions setting has changed
            static void OnViewingRestrictionsChanged(const JSONRPC& _module_, const string& viewingRestrictions)
            {
                JsonData::UserSettings::SetViewingRestrictionsParamsInfo _params_;
                _params_.ViewingRestrictions = viewingRestrictions;

                OnViewingRestrictionsChanged(_module_, _params_);
            }

            // Event: 'onViewingRestrictionsWindowChanged' - The ViewingRestrictionsWindow setting has changed
            static void OnViewingRestrictionsWindowChanged(const JSONRPC& _module_,
                     const JsonData::UserSettings::SetViewingRestrictionsWindowParamsInfo& params)
            {
                _module_.Notify(_T("onViewingRestrictionsWindowChanged"), params);
            }

            // Event: 'onViewingRestrictionsWindowChanged' - The ViewingRestrictionsWindow setting has changed
            static void OnViewingRestrictionsWindowChanged(const JSONRPC& _module_, const Core::JSON::String& viewingRestrictionsWindow)
            {
                JsonData::UserSettings::SetViewingRestrictionsWindowParamsInfo _params_;
                _params_.ViewingRestrictionsWindow = viewingRestrictionsWindow;

                OnViewingRestrictionsWindowChanged(_module_, _params_);
            }

            // Event: 'onViewingRestrictionsWindowChanged' - The ViewingRestrictionsWindow setting has changed
            static void OnViewingRestrictionsWindowChanged(const JSONRPC& _module_, const string& viewingRestrictionsWindow)
            {
                JsonData::UserSettings::SetViewingRestrictionsWindowParamsInfo _params_;
                _params_.ViewingRestrictionsWindow = viewingRestrictionsWindow;

                OnViewingRestrictionsWindowChanged(_module_, _params_);
            }

            // Event: 'onLiveWatershedChanged' - The LiveWatershed setting has changed
            static void OnLiveWatershedChanged(const JSONRPC& _module_, const JsonData::UserSettings::SetLiveWatershedParamsInfo& params)
            {
                _module_.Notify(_T("onLiveWatershedChanged"), params);
            }

            // Event: 'onLiveWatershedChanged' - The LiveWatershed setting has changed
            static void OnLiveWatershedChanged(const JSONRPC& _module_, const Core::JSON::Boolean& liveWatershed)
            {
                JsonData::UserSettings::SetLiveWatershedParamsInfo _params_;
                _params_.LiveWatershed = liveWatershed;

                OnLiveWatershedChanged(_module_, _params_);
            }

            // Event: 'onLiveWatershedChanged' - The LiveWatershed setting has changed
            static void OnLiveWatershedChanged(const JSONRPC& _module_, const bool& liveWatershed)
            {
                JsonData::UserSettings::SetLiveWatershedParamsInfo _params_;
                _params_.LiveWatershed = liveWatershed;

                OnLiveWatershedChanged(_module_, _params_);
            }

            // Event: 'onPlaybackWatershedChanged' - The PlaybackWatershed setting has changed
            static void OnPlaybackWatershedChanged(const JSONRPC& _module_, const JsonData::UserSettings::SetPlaybackWatershedParamsInfo& params)
            {
                _module_.Notify(_T("onPlaybackWatershedChanged"), params);
            }

            // Event: 'onPlaybackWatershedChanged' - The PlaybackWatershed setting has changed
            static void OnPlaybackWatershedChanged(const JSONRPC& _module_, const Core::JSON::Boolean& playbackWatershed)
            {
                JsonData::UserSettings::SetPlaybackWatershedParamsInfo _params_;
                _params_.PlaybackWatershed = playbackWatershed;

                OnPlaybackWatershedChanged(_module_, _params_);
            }

            // Event: 'onPlaybackWatershedChanged' - The PlaybackWatershed setting has changed
            static void OnPlaybackWatershedChanged(const JSONRPC& _module_, const bool& playbackWatershed)
            {
                JsonData::UserSettings::SetPlaybackWatershedParamsInfo _params_;
                _params_.PlaybackWatershed = playbackWatershed;

                OnPlaybackWatershedChanged(_module_, _params_);
            }

            // Event: 'onBlockNotRatedContentChanged' - The BlockNotRatedContent setting has changed
            static void OnBlockNotRatedContentChanged(const JSONRPC& _module_, const JsonData::UserSettings::SetBlockNotRatedContentParamsInfo& params)
            {
                _module_.Notify(_T("onBlockNotRatedContentChanged"), params);
            }

            // Event: 'onBlockNotRatedContentChanged' - The BlockNotRatedContent setting has changed
            static void OnBlockNotRatedContentChanged(const JSONRPC& _module_, const Core::JSON::Boolean& blockNotRatedContent)
            {
                JsonData::UserSettings::SetBlockNotRatedContentParamsInfo _params_;
                _params_.BlockNotRatedContent = blockNotRatedContent;

                OnBlockNotRatedContentChanged(_module_, _params_);
            }

            // Event: 'onBlockNotRatedContentChanged' - The BlockNotRatedContent setting has changed
            static void OnBlockNotRatedContentChanged(const JSONRPC& _module_, const bool& blockNotRatedContent)
            {
                JsonData::UserSettings::SetBlockNotRatedContentParamsInfo _params_;
                _params_.BlockNotRatedContent = blockNotRatedContent;

                OnBlockNotRatedContentChanged(_module_, _params_);
            }

            // Event: 'onPinOnPurchaseChanged' - The PinOnPurchase setting has changed
            static void OnPinOnPurchaseChanged(const JSONRPC& _module_, const JsonData::UserSettings::SetPinOnPurchaseParamsInfo& params)
            {
                _module_.Notify(_T("onPinOnPurchaseChanged"), params);
            }

            // Event: 'onPinOnPurchaseChanged' - The PinOnPurchase setting has changed
            static void OnPinOnPurchaseChanged(const JSONRPC& _module_, const Core::JSON::Boolean& pinOnPurchase)
            {
                JsonData::UserSettings::SetPinOnPurchaseParamsInfo _params_;
                _params_.PinOnPurchase = pinOnPurchase;

                OnPinOnPurchaseChanged(_module_, _params_);
            }

            // Event: 'onPinOnPurchaseChanged' - The PinOnPurchase setting has changed
            static void OnPinOnPurchaseChanged(const JSONRPC& _module_, const bool& pinOnPurchase)
            {
                JsonData::UserSettings::SetPinOnPurchaseParamsInfo _params_;
                _params_.PinOnPurchase = pinOnPurchase;

                OnPinOnPurchaseChanged(_module_, _params_);
            }

            // Event: 'onHighContrastChanged' - Triggered after the high contrast settings changes
            static void OnHighContrastChanged(const JSONRPC& _module_, const JsonData::UserSettings::SetAudioDescriptionParamsInfo& params)
            {
                _module_.Notify(_T("onHighContrastChanged"), params);
            }

            // Event: 'onHighContrastChanged' - Triggered after the high contrast settings changes
            static void OnHighContrastChanged(const JSONRPC& _module_, const Core::JSON::Boolean& enabled)
            {
                JsonData::UserSettings::SetAudioDescriptionParamsInfo _params_;
                _params_.Enabled = enabled;

                OnHighContrastChanged(_module_, _params_);
            }

            // Event: 'onHighContrastChanged' - Triggered after the high contrast settings changes
            static void OnHighContrastChanged(const JSONRPC& _module_, const bool& enabled)
            {
                JsonData::UserSettings::SetAudioDescriptionParamsInfo _params_;
                _params_.Enabled = enabled;

                OnHighContrastChanged(_module_, _params_);
            }

            // Event: 'onVoiceGuidanceChanged' - Triggered after the voice guidance enabled settings changes
            static void OnVoiceGuidanceChanged(const JSONRPC& _module_, const JsonData::UserSettings::SetAudioDescriptionParamsInfo& params)
            {
                _module_.Notify(_T("onVoiceGuidanceChanged"), params);
            }

            // Event: 'onVoiceGuidanceChanged' - Triggered after the voice guidance enabled settings changes
            static void OnVoiceGuidanceChanged(const JSONRPC& _module_, const Core::JSON::Boolean& enabled)
            {
                JsonData::UserSettings::SetAudioDescriptionParamsInfo _params_;
                _params_.Enabled = enabled;

                OnVoiceGuidanceChanged(_module_, _params_);
            }

            // Event: 'onVoiceGuidanceChanged' - Triggered after the voice guidance enabled settings changes
            static void OnVoiceGuidanceChanged(const JSONRPC& _module_, const bool& enabled)
            {
                JsonData::UserSettings::SetAudioDescriptionParamsInfo _params_;
                _params_.Enabled = enabled;

                OnVoiceGuidanceChanged(_module_, _params_);
            }

            // Event: 'onVoiceGuidanceRateChanged' - Triggered after the voice guidance rate changed
            static void OnVoiceGuidanceRateChanged(const JSONRPC& _module_, const JsonData::UserSettings::SetVoiceGuidanceRateParamsInfo& params)
            {
                _module_.Notify(_T("onVoiceGuidanceRateChanged"), params);
            }

            // Event: 'onVoiceGuidanceRateChanged' - Triggered after the voice guidance rate changed
            static void OnVoiceGuidanceRateChanged(const JSONRPC& _module_, const Core::JSON::Double& rate)
            {
                JsonData::UserSettings::SetVoiceGuidanceRateParamsInfo _params_;
                _params_.Rate = rate;

                OnVoiceGuidanceRateChanged(_module_, _params_);
            }

            // Event: 'onVoiceGuidanceRateChanged' - Triggered after the voice guidance rate changed
            static void OnVoiceGuidanceRateChanged(const JSONRPC& _module_, const double& rate)
            {
                JsonData::UserSettings::SetVoiceGuidanceRateParamsInfo _params_;
                _params_.Rate = rate;

                OnVoiceGuidanceRateChanged(_module_, _params_);
            }

            // Event: 'onVoiceGuidanceHintsChanged' - Triggered after the voice guidance hints changes
            static void OnVoiceGuidanceHintsChanged(const JSONRPC& _module_, const JsonData::UserSettings::SetVoiceGuidanceHintsParamsInfo& params)
            {
                _module_.Notify(_T("onVoiceGuidanceHintsChanged"), params);
            }

            // Event: 'onVoiceGuidanceHintsChanged' - Triggered after the voice guidance hints changes
            static void OnVoiceGuidanceHintsChanged(const JSONRPC& _module_, const Core::JSON::Boolean& hints)
            {
                JsonData::UserSettings::SetVoiceGuidanceHintsParamsInfo _params_;
                _params_.Hints = hints;

                OnVoiceGuidanceHintsChanged(_module_, _params_);
            }

            // Event: 'onVoiceGuidanceHintsChanged' - Triggered after the voice guidance hints changes
            static void OnVoiceGuidanceHintsChanged(const JSONRPC& _module_, const bool& hints)
            {
                JsonData::UserSettings::SetVoiceGuidanceHintsParamsInfo _params_;
                _params_.Hints = hints;

                OnVoiceGuidanceHintsChanged(_module_, _params_);
            }

            // Event: 'onContentPinChanged' - The ContentPin setting has changed
            static void OnContentPinChanged(const JSONRPC& _module_, const JsonData::UserSettings::SetContentPinParamsInfo& params)
            {
                _module_.Notify(_T("onContentPinChanged"), params);
            }

            // Event: 'onContentPinChanged' - The ContentPin setting has changed
            static void OnContentPinChanged(const JSONRPC& _module_, const Core::JSON::String& contentPin)
            {
                JsonData::UserSettings::SetContentPinParamsInfo _params_;
                _params_.ContentPin = contentPin;

                OnContentPinChanged(_module_, _params_);
            }

            // Event: 'onContentPinChanged' - The ContentPin setting has changed
            static void OnContentPinChanged(const JSONRPC& _module_, const string& contentPin)
            {
                JsonData::UserSettings::SetContentPinParamsInfo _params_;
                _params_.ContentPin = contentPin;

                OnContentPinChanged(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JUserSettings

} // namespace Exchange

} // namespace WPEFramework

