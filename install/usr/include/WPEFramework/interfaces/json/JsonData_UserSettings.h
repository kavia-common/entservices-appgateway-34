// C++ classes for UserSettings API JSON-RPC API.
// Generated automatically from 'IUserSettings.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IUserSettings.h>

namespace WPEFramework {

namespace JsonData {

    namespace UserSettings {

        // Common classes
        //

        class SetAudioDescriptionParamsInfo : public Core::JSON::Container {
        public:
            SetAudioDescriptionParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("enabled"), &Enabled);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetAudioDescriptionParamsInfo(const SetAudioDescriptionParamsInfo&) = delete;
            SetAudioDescriptionParamsInfo& operator=(const SetAudioDescriptionParamsInfo&) = delete;

        public:
            Core::JSON::Boolean Enabled; // Enabled/Disabled
        }; // class SetAudioDescriptionParamsInfo

        class SetBlockNotRatedContentParamsInfo : public Core::JSON::Container {
        public:
            SetBlockNotRatedContentParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("blockNotRatedContent"), &BlockNotRatedContent);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetBlockNotRatedContentParamsInfo(const SetBlockNotRatedContentParamsInfo&) = delete;
            SetBlockNotRatedContentParamsInfo& operator=(const SetBlockNotRatedContentParamsInfo&) = delete;

        public:
            Core::JSON::Boolean BlockNotRatedContent; // Enabled/Disabled
        }; // class SetBlockNotRatedContentParamsInfo

        class SetContentPinParamsInfo : public Core::JSON::Container {
        public:
            SetContentPinParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("contentPin"), &ContentPin);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetContentPinParamsInfo(const SetContentPinParamsInfo&) = delete;
            SetContentPinParamsInfo& operator=(const SetContentPinParamsInfo&) = delete;

        public:
            Core::JSON::String ContentPin; // A string of four decimal digits that represents the content PIN.
        }; // class SetContentPinParamsInfo

        class SetLiveWatershedParamsInfo : public Core::JSON::Container {
        public:
            SetLiveWatershedParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("liveWatershed"), &LiveWatershed);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetLiveWatershedParamsInfo(const SetLiveWatershedParamsInfo&) = delete;
            SetLiveWatershedParamsInfo& operator=(const SetLiveWatershedParamsInfo&) = delete;

        public:
            Core::JSON::Boolean LiveWatershed; // Enabled/Disabled
        }; // class SetLiveWatershedParamsInfo

        class SetPinControlParamsInfo : public Core::JSON::Container {
        public:
            SetPinControlParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("pinControl"), &PinControl);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetPinControlParamsInfo(const SetPinControlParamsInfo&) = delete;
            SetPinControlParamsInfo& operator=(const SetPinControlParamsInfo&) = delete;

        public:
            Core::JSON::Boolean PinControl; // Enabled/Disabled
        }; // class SetPinControlParamsInfo

        class SetPinOnPurchaseParamsInfo : public Core::JSON::Container {
        public:
            SetPinOnPurchaseParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("pinOnPurchase"), &PinOnPurchase);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetPinOnPurchaseParamsInfo(const SetPinOnPurchaseParamsInfo&) = delete;
            SetPinOnPurchaseParamsInfo& operator=(const SetPinOnPurchaseParamsInfo&) = delete;

        public:
            Core::JSON::Boolean PinOnPurchase; // Enabled/Disabled
        }; // class SetPinOnPurchaseParamsInfo

        class SetPlaybackWatershedParamsInfo : public Core::JSON::Container {
        public:
            SetPlaybackWatershedParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("playbackWatershed"), &PlaybackWatershed);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetPlaybackWatershedParamsInfo(const SetPlaybackWatershedParamsInfo&) = delete;
            SetPlaybackWatershedParamsInfo& operator=(const SetPlaybackWatershedParamsInfo&) = delete;

        public:
            Core::JSON::Boolean PlaybackWatershed; // Enabled/Disabled
        }; // class SetPlaybackWatershedParamsInfo

        class SetPreferredAudioLanguagesParamsInfo : public Core::JSON::Container {
        public:
            SetPreferredAudioLanguagesParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("preferredLanguages"), &PreferredLanguages);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetPreferredAudioLanguagesParamsInfo(const SetPreferredAudioLanguagesParamsInfo&) = delete;
            SetPreferredAudioLanguagesParamsInfo& operator=(const SetPreferredAudioLanguagesParamsInfo&) = delete;

        public:
            Core::JSON::String PreferredLanguages; // PreferredLanguages
        }; // class SetPreferredAudioLanguagesParamsInfo

        class SetPreferredClosedCaptionServiceParamsInfo : public Core::JSON::Container {
        public:
            SetPreferredClosedCaptionServiceParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("service"), &Service);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetPreferredClosedCaptionServiceParamsInfo(const SetPreferredClosedCaptionServiceParamsInfo&) = delete;
            SetPreferredClosedCaptionServiceParamsInfo& operator=(const SetPreferredClosedCaptionServiceParamsInfo&) = delete;

        public:
            Core::JSON::String Service; // Identifies the service to display e.g. "CC3".
        }; // class SetPreferredClosedCaptionServiceParamsInfo

        class SetPresentationLanguageParamsInfo : public Core::JSON::Container {
        public:
            SetPresentationLanguageParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("presentationLanguage"), &PresentationLanguage);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetPresentationLanguageParamsInfo(const SetPresentationLanguageParamsInfo&) = delete;
            SetPresentationLanguageParamsInfo& operator=(const SetPresentationLanguageParamsInfo&) = delete;

        public:
            Core::JSON::String PresentationLanguage; // "en-US", "es-US", "en-CA", "fr-CA"
        }; // class SetPresentationLanguageParamsInfo

        class SetPrivacyModeParamsInfo : public Core::JSON::Container {
        public:
            SetPrivacyModeParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("privacyMode"), &PrivacyMode);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetPrivacyModeParamsInfo(const SetPrivacyModeParamsInfo&) = delete;
            SetPrivacyModeParamsInfo& operator=(const SetPrivacyModeParamsInfo&) = delete;

        public:
            Core::JSON::String PrivacyMode; // "SHARE", "DO_NOT_SHARE"
        }; // class SetPrivacyModeParamsInfo

        class SetViewingRestrictionsParamsInfo : public Core::JSON::Container {
        public:
            SetViewingRestrictionsParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("viewingRestrictions"), &ViewingRestrictions);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetViewingRestrictionsParamsInfo(const SetViewingRestrictionsParamsInfo&) = delete;
            SetViewingRestrictionsParamsInfo& operator=(const SetViewingRestrictionsParamsInfo&) = delete;

        public:
            Core::JSON::String ViewingRestrictions; // A JSON document that describes the rating scheme(s) and ratings that are blocked.
        }; // class SetViewingRestrictionsParamsInfo

        class SetViewingRestrictionsWindowParamsInfo : public Core::JSON::Container {
        public:
            SetViewingRestrictionsWindowParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("viewingRestrictionsWindow"), &ViewingRestrictionsWindow);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetViewingRestrictionsWindowParamsInfo(const SetViewingRestrictionsWindowParamsInfo&) = delete;
            SetViewingRestrictionsWindowParamsInfo& operator=(const SetViewingRestrictionsWindowParamsInfo&) = delete;

        public:
            Core::JSON::String ViewingRestrictionsWindow; // A project-specific representation of the time interval.Eg: "ALWAYS"
        }; // class SetViewingRestrictionsWindowParamsInfo

        class SetVoiceGuidanceHintsParamsInfo : public Core::JSON::Container {
        public:
            SetVoiceGuidanceHintsParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("hints"), &Hints);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetVoiceGuidanceHintsParamsInfo(const SetVoiceGuidanceHintsParamsInfo&) = delete;
            SetVoiceGuidanceHintsParamsInfo& operator=(const SetVoiceGuidanceHintsParamsInfo&) = delete;

        public:
            Core::JSON::Boolean Hints; // Enabled/Disabled
        }; // class SetVoiceGuidanceHintsParamsInfo

        class SetVoiceGuidanceRateParamsInfo : public Core::JSON::Container {
        public:
            SetVoiceGuidanceRateParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("rate"), &Rate);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetVoiceGuidanceRateParamsInfo(const SetVoiceGuidanceRateParamsInfo&) = delete;
            SetVoiceGuidanceRateParamsInfo& operator=(const SetVoiceGuidanceRateParamsInfo&) = delete;

        public:
            Core::JSON::Double Rate; // Sets Voice Guidance rate
        }; // class SetVoiceGuidanceRateParamsInfo

        // Method params/result classes
        //

    } // namespace UserSettings

} // namespace JsonData

}

