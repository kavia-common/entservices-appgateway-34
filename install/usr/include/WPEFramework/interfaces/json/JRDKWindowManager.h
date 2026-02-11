// Generated automatically from 'IRDKWindowManager.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_RDKWindowManager.h"
#include <interfaces/IRDKWindowManager.h>

namespace WPEFramework {

namespace Exchange {

    namespace JRDKWindowManager {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IRDKWindowManager* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JRDKWindowManager"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'createDisplay' - Create the display window
            _module_.Register<JsonData::RDKWindowManager::CreateDisplayParamsData, void>(_T("createDisplay"), 
                [_impl_](const JsonData::RDKWindowManager::CreateDisplayParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _displayParams{params.DisplayParams};

                    _errorCode = _impl_->CreateDisplay(_displayParams);

                    return (_errorCode);
                });

            // Method: 'getApps' - Get the list of Apps which are currently active and available
            _module_.Register<void, Core::JSON::String>(_T("getApps"), 
                [_impl_](Core::JSON::String& appsIds) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _appsIds{};

                    _errorCode = _impl_->GetApps(_appsIds);

                    if (_errorCode == Core::ERROR_NONE) {
                        appsIds = _appsIds;
                    }

                    return (_errorCode);
                });

            // Method: 'addKeyIntercept' - Registers a key intercept for a specific key code and client
            _module_.Register<JsonData::RDKWindowManager::AddKeyInterceptParamsInfo, void>(_T("addKeyIntercept"), 
                [_impl_](const JsonData::RDKWindowManager::AddKeyInterceptParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _intercept{params.Intercept};

                    _errorCode = _impl_->AddKeyIntercept(_intercept);

                    return (_errorCode);
                });

            // Method: 'addKeyIntercepts' - Registers multiple key intercepts in a single operation
            _module_.Register<JsonData::RDKWindowManager::AddKeyInterceptsParamsData, void>(_T("addKeyIntercepts"), 
                [_impl_](const JsonData::RDKWindowManager::AddKeyInterceptsParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _intercepts{params.Intercepts};

                    _errorCode = _impl_->AddKeyIntercepts(_intercepts);

                    return (_errorCode);
                });

            // Method: 'removeKeyIntercept' - Removes a key intercept for a specific key code and client
            _module_.Register<JsonData::RDKWindowManager::AddKeyInterceptParamsInfo, void>(_T("removeKeyIntercept"), 
                [_impl_](const JsonData::RDKWindowManager::AddKeyInterceptParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _intercept{params.Intercept};

                    _errorCode = _impl_->RemoveKeyIntercept(_intercept);

                    return (_errorCode);
                });

            // Method: 'addKeyListener' - Registers listeners for specific keys
            _module_.Register<JsonData::RDKWindowManager::AddKeyListenerParamsInfo, void>(_T("addKeyListener"), 
                [_impl_](const JsonData::RDKWindowManager::AddKeyListenerParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _keyListeners{params.KeyListeners};

                    _errorCode = _impl_->AddKeyListener(_keyListeners);

                    return (_errorCode);
                });

            // Method: 'removeKeyListener' - Removes listeners for specific keys
            _module_.Register<JsonData::RDKWindowManager::AddKeyListenerParamsInfo, void>(_T("removeKeyListener"), 
                [_impl_](const JsonData::RDKWindowManager::AddKeyListenerParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _keyListeners{params.KeyListeners};

                    _errorCode = _impl_->RemoveKeyListener(_keyListeners);

                    return (_errorCode);
                });

            // Method: 'injectKey' - Simulates a key press event with optional modifiers
            _module_.Register<JsonData::RDKWindowManager::InjectKeyParamsData, void>(_T("injectKey"), 
                [_impl_](const JsonData::RDKWindowManager::InjectKeyParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _keyCode{params.KeyCode};
                    const string _modifiers{params.Modifiers};

                    _errorCode = _impl_->InjectKey(_keyCode, _modifiers);

                    return (_errorCode);
                });

            // Method: 'generateKey' - Generates a key event for the specified keys and client
            _module_.Register<JsonData::RDKWindowManager::GenerateKeyParamsData, void>(_T("generateKey"), 
                [_impl_](const JsonData::RDKWindowManager::GenerateKeyParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _keys{params.Keys};
                    const string _client{params.Client};

                    _errorCode = _impl_->GenerateKey(_keys, _client);

                    return (_errorCode);
                });

            // Method: 'enableInactivityReporting' - Enables the inactivity reporting
            _module_.Register<JsonData::RDKWindowManager::EnableInactivityReportingParamsInfo, void>(_T("enableInactivityReporting"), 
                [_impl_](const JsonData::RDKWindowManager::EnableInactivityReportingParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _enable{params.Enable};

                    _errorCode = _impl_->EnableInactivityReporting(_enable);

                    return (_errorCode);
                });

            // Method: 'setInactivityInterval' - Sets inactivity interval if EnableUserInactivity feature is enabled
            _module_.Register<JsonData::RDKWindowManager::SetInactivityIntervalParamsData, void>(_T("setInactivityInterval"), 
                [_impl_](const JsonData::RDKWindowManager::SetInactivityIntervalParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _interval{params.Interval};

                    _errorCode = _impl_->SetInactivityInterval(_interval);

                    return (_errorCode);
                });

            // Method: 'resetInactivityTime' - Resets inactivity interval if EnableUserInactivity feature is enabled
            _module_.Register<void, void>(_T("resetInactivityTime"), 
                [_impl_]() -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    _errorCode = _impl_->ResetInactivityTime();

                    return (_errorCode);
                });

            // Method: 'enableKeyRepeats' - Key repeats are enabled/disabled
            _module_.Register<JsonData::RDKWindowManager::EnableInactivityReportingParamsInfo, void>(_T("enableKeyRepeats"), 
                [_impl_](const JsonData::RDKWindowManager::EnableInactivityReportingParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _enable{params.Enable};

                    _errorCode = _impl_->EnableKeyRepeats(_enable);

                    return (_errorCode);
                });

            // Method: 'getKeyRepeatsEnabled' - Retrieves the flag determining whether keyRepeat true/false
            _module_.Register<void, Core::JSON::Boolean>(_T("getKeyRepeatsEnabled"), 
                [_impl_](Core::JSON::Boolean& keyRepeat) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    bool _keyRepeat{};

                    _errorCode = _impl_->GetKeyRepeatsEnabled(_keyRepeat);

                    if (_errorCode == Core::ERROR_NONE) {
                        keyRepeat = _keyRepeat;
                    }

                    return (_errorCode);
                });

            // Method: 'ignoreKeyInputs' - Ignore key inputs
            _module_.Register<JsonData::RDKWindowManager::IgnoreKeyInputsParamsData, void>(_T("ignoreKeyInputs"), 
                [_impl_](const JsonData::RDKWindowManager::IgnoreKeyInputsParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _ignore{params.Ignore};

                    _errorCode = _impl_->IgnoreKeyInputs(_ignore);

                    return (_errorCode);
                });

            // Method: 'enableInputEvents' - Enables KeyInputEvents for list of clients specified
            _module_.Register<JsonData::RDKWindowManager::EnableInputEventsParamsData, void>(_T("enableInputEvents"), 
                [_impl_](const JsonData::RDKWindowManager::EnableInputEventsParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _clients{params.Clients};
                    const bool _enable{params.Enable};

                    _errorCode = _impl_->EnableInputEvents(_clients, _enable);

                    return (_errorCode);
                });

            // Method: 'keyRepeatConfig' - Enables KeyInputEvents for list of clients specified
            _module_.Register<JsonData::RDKWindowManager::KeyRepeatConfigParamsData, void>(_T("keyRepeatConfig"), 
                [_impl_](const JsonData::RDKWindowManager::KeyRepeatConfigParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _input{params.Input};
                    const string _keyConfig{params.KeyConfig};

                    _errorCode = _impl_->KeyRepeatConfig(_input, _keyConfig);

                    return (_errorCode);
                });

            // Method: 'setFocus' - Sets the focus to the app with the app id
            _module_.Register<JsonData::RDKWindowManager::SetFocusParamsInfo, void>(_T("setFocus"), 
                [_impl_](const JsonData::RDKWindowManager::SetFocusParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _client{params.Client};

                    _errorCode = _impl_->SetFocus(_client);

                    return (_errorCode);
                });

            // Method: 'setVisible' - Sets the visibility of the given client or appInstanceId
            _module_.Register<JsonData::RDKWindowManager::SetVisibleParamsData, void>(_T("setVisible"), 
                [_impl_](const JsonData::RDKWindowManager::SetVisibleParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _client{params.Client};
                    const bool _visible{params.Visible};

                    _errorCode = _impl_->SetVisible(_client, _visible);

                    return (_errorCode);
                });

            // Method: 'renderReady' - To get the status of first frame is rendered or not
            _module_.Register<JsonData::RDKWindowManager::SetFocusParamsInfo, Core::JSON::Boolean>(_T("renderReady"), 
                [_impl_](const JsonData::RDKWindowManager::SetFocusParamsInfo& params, Core::JSON::Boolean& status) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _client{params.Client};
                    bool _status{};

                    _errorCode = _impl_->RenderReady(_client, _status);

                    if (_errorCode == Core::ERROR_NONE) {
                        status = _status;
                    }

                    return (_errorCode);
                });

            // Method: 'enableDisplayRender' - Enable or disable the rendering of a Wayland display
            _module_.Register<JsonData::RDKWindowManager::EnableDisplayRenderParamsData, void>(_T("enableDisplayRender"), 
                [_impl_](const JsonData::RDKWindowManager::EnableDisplayRenderParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _client{params.Client};
                    const bool _enable{params.Enable};

                    _errorCode = _impl_->EnableDisplayRender(_client, _enable);

                    return (_errorCode);
                });

            // Method: 'getLastKeyInfo' - Retrieves information about the most recent key press event, including the key code, modifier flags,
                    //  and the timestamp in seconds when the key was pressed
            _module_.Register<void, JsonData::RDKWindowManager::GetLastKeyInfoResultData>(_T("getLastKeyInfo"), 
                [_impl_](JsonData::RDKWindowManager::GetLastKeyInfoResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    uint32_t _keyCode{};
                    uint32_t _modifiers{};
                    uint64_t _timestampInSeconds{};

                    _errorCode = _impl_->GetLastKeyInfo(_keyCode, _modifiers, _timestampInSeconds);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.KeyCode = _keyCode;
                        result.Modifiers = _modifiers;
                        result.TimestampInSeconds = _timestampInSeconds;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("createDisplay"));
            _module_.Unregister(_T("getApps"));
            _module_.Unregister(_T("addKeyIntercept"));
            _module_.Unregister(_T("addKeyIntercepts"));
            _module_.Unregister(_T("removeKeyIntercept"));
            _module_.Unregister(_T("addKeyListener"));
            _module_.Unregister(_T("removeKeyListener"));
            _module_.Unregister(_T("injectKey"));
            _module_.Unregister(_T("generateKey"));
            _module_.Unregister(_T("enableInactivityReporting"));
            _module_.Unregister(_T("setInactivityInterval"));
            _module_.Unregister(_T("resetInactivityTime"));
            _module_.Unregister(_T("enableKeyRepeats"));
            _module_.Unregister(_T("getKeyRepeatsEnabled"));
            _module_.Unregister(_T("ignoreKeyInputs"));
            _module_.Unregister(_T("enableInputEvents"));
            _module_.Unregister(_T("keyRepeatConfig"));
            _module_.Unregister(_T("setFocus"));
            _module_.Unregister(_T("setVisible"));
            _module_.Unregister(_T("renderReady"));
            _module_.Unregister(_T("enableDisplayRender"));
            _module_.Unregister(_T("getLastKeyInfo"));
        }

        namespace Event {

            // Event: 'onUserInactivity' - Posting the client is inactive state
            static void OnUserInactivity(const JSONRPC& _module_, const JsonData::RDKWindowManager::OnUserInactivityParamsData& params)
            {
                _module_.Notify(_T("onUserInactivity"), params);
            }

            // Event: 'onUserInactivity' - Posting the client is inactive state
            static void OnUserInactivity(const JSONRPC& _module_, const Core::JSON::Double& minutes)
            {
                JsonData::RDKWindowManager::OnUserInactivityParamsData _params_;
                _params_.Minutes = minutes;

                OnUserInactivity(_module_, _params_);
            }

            // Event: 'onUserInactivity' - Posting the client is inactive state
            static void OnUserInactivity(const JSONRPC& _module_, const double& minutes)
            {
                JsonData::RDKWindowManager::OnUserInactivityParamsData _params_;
                _params_.Minutes = minutes;

                OnUserInactivity(_module_, _params_);
            }

            // Event: 'onDisconnected' - Notifies when an application is disconnected
            static void OnDisconnected(const JSONRPC& _module_, const JsonData::RDKWindowManager::SetFocusParamsInfo& params)
            {
                _module_.Notify(_T("onDisconnected"), params);
            }

            // Event: 'onDisconnected' - Notifies when an application is disconnected
            static void OnDisconnected(const JSONRPC& _module_, const Core::JSON::String& client)
            {
                JsonData::RDKWindowManager::SetFocusParamsInfo _params_;
                _params_.Client = client;

                OnDisconnected(_module_, _params_);
            }

            // Event: 'onDisconnected' - Notifies when an application is disconnected
            static void OnDisconnected(const JSONRPC& _module_, const string& client)
            {
                JsonData::RDKWindowManager::SetFocusParamsInfo _params_;
                _params_.Client = client;

                OnDisconnected(_module_, _params_);
            }

            // Event: 'onReady' - Posting the client for first frame ready
            static void OnReady(const JSONRPC& _module_, const JsonData::RDKWindowManager::SetFocusParamsInfo& params)
            {
                _module_.Notify(_T("onReady"), params);
            }

            // Event: 'onReady' - Posting the client for first frame ready
            static void OnReady(const JSONRPC& _module_, const Core::JSON::String& client)
            {
                JsonData::RDKWindowManager::SetFocusParamsInfo _params_;
                _params_.Client = client;

                OnReady(_module_, _params_);
            }

            // Event: 'onReady' - Posting the client for first frame ready
            static void OnReady(const JSONRPC& _module_, const string& client)
            {
                JsonData::RDKWindowManager::SetFocusParamsInfo _params_;
                _params_.Client = client;

                OnReady(_module_, _params_);
            }

            // Event: 'onConnected' - Notifies when an application is connected
            static void OnConnected(const JSONRPC& _module_, const JsonData::RDKWindowManager::OnConnectedParamsInfo& params)
            {
                _module_.Notify(_T("onConnected"), params);
            }

            // Event: 'onConnected' - Notifies when an application is connected
            static void OnConnected(const JSONRPC& _module_, const Core::JSON::String& appInstanceId)
            {
                JsonData::RDKWindowManager::OnConnectedParamsInfo _params_;
                _params_.AppInstanceId = appInstanceId;

                OnConnected(_module_, _params_);
            }

            // Event: 'onConnected' - Notifies when an application is connected
            static void OnConnected(const JSONRPC& _module_, const string& appInstanceId)
            {
                JsonData::RDKWindowManager::OnConnectedParamsInfo _params_;
                _params_.AppInstanceId = appInstanceId;

                OnConnected(_module_, _params_);
            }

            // Event: 'onVisible' - Notifies when an application is visible
            static void OnVisible(const JSONRPC& _module_, const JsonData::RDKWindowManager::OnConnectedParamsInfo& params)
            {
                _module_.Notify(_T("onVisible"), params);
            }

            // Event: 'onVisible' - Notifies when an application is visible
            static void OnVisible(const JSONRPC& _module_, const Core::JSON::String& appInstanceId)
            {
                JsonData::RDKWindowManager::OnConnectedParamsInfo _params_;
                _params_.AppInstanceId = appInstanceId;

                OnVisible(_module_, _params_);
            }

            // Event: 'onVisible' - Notifies when an application is visible
            static void OnVisible(const JSONRPC& _module_, const string& appInstanceId)
            {
                JsonData::RDKWindowManager::OnConnectedParamsInfo _params_;
                _params_.AppInstanceId = appInstanceId;

                OnVisible(_module_, _params_);
            }

            // Event: 'onHidden' - Notifies when an application is hidden
            static void OnHidden(const JSONRPC& _module_, const JsonData::RDKWindowManager::OnConnectedParamsInfo& params)
            {
                _module_.Notify(_T("onHidden"), params);
            }

            // Event: 'onHidden' - Notifies when an application is hidden
            static void OnHidden(const JSONRPC& _module_, const Core::JSON::String& appInstanceId)
            {
                JsonData::RDKWindowManager::OnConnectedParamsInfo _params_;
                _params_.AppInstanceId = appInstanceId;

                OnHidden(_module_, _params_);
            }

            // Event: 'onHidden' - Notifies when an application is hidden
            static void OnHidden(const JSONRPC& _module_, const string& appInstanceId)
            {
                JsonData::RDKWindowManager::OnConnectedParamsInfo _params_;
                _params_.AppInstanceId = appInstanceId;

                OnHidden(_module_, _params_);
            }

            // Event: 'onFocus' - Notifies when an application is in focus
            static void OnFocus(const JSONRPC& _module_, const JsonData::RDKWindowManager::OnConnectedParamsInfo& params)
            {
                _module_.Notify(_T("onFocus"), params);
            }

            // Event: 'onFocus' - Notifies when an application is in focus
            static void OnFocus(const JSONRPC& _module_, const Core::JSON::String& appInstanceId)
            {
                JsonData::RDKWindowManager::OnConnectedParamsInfo _params_;
                _params_.AppInstanceId = appInstanceId;

                OnFocus(_module_, _params_);
            }

            // Event: 'onFocus' - Notifies when an application is in focus
            static void OnFocus(const JSONRPC& _module_, const string& appInstanceId)
            {
                JsonData::RDKWindowManager::OnConnectedParamsInfo _params_;
                _params_.AppInstanceId = appInstanceId;

                OnFocus(_module_, _params_);
            }

            // Event: 'onBlur' - Notifies when an application is blurred
            static void OnBlur(const JSONRPC& _module_, const JsonData::RDKWindowManager::OnConnectedParamsInfo& params)
            {
                _module_.Notify(_T("onBlur"), params);
            }

            // Event: 'onBlur' - Notifies when an application is blurred
            static void OnBlur(const JSONRPC& _module_, const Core::JSON::String& appInstanceId)
            {
                JsonData::RDKWindowManager::OnConnectedParamsInfo _params_;
                _params_.AppInstanceId = appInstanceId;

                OnBlur(_module_, _params_);
            }

            // Event: 'onBlur' - Notifies when an application is blurred
            static void OnBlur(const JSONRPC& _module_, const string& appInstanceId)
            {
                JsonData::RDKWindowManager::OnConnectedParamsInfo _params_;
                _params_.AppInstanceId = appInstanceId;

                OnBlur(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JRDKWindowManager

} // namespace Exchange

} // namespace WPEFramework

