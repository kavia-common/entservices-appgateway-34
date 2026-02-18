# Step 23 AppGateway plugin build/install fix

This repository’s `appgateway_L1_tests_withoutACT.sh` has been updated so that **Step 23**:

- Configures the entservices-appgateway build with:
  - `-DRDK_SERVICES_L1_TEST=ON`
  - `-DPLUGIN_APPGATEWAY=ON` (required to ensure `add_subdirectory(AppGateway)` runs)
- Logs the **full CMake configure command line** (including `-DPLUGIN_APPGATEWAY=ON`) before build/test/coverage.
- Verifies the plugin shared library exists after install under:
  - `${INSTALL_USR}/lib/wpeframework/plugins/`
- Copies the plugin `.so` into the system plugin location as well (when permitted):
  - `/usr/lib/wpeframework/plugins/`

Expected plugin artifact names/paths:
- `${INSTALL_USR}/lib/wpeframework/plugins/libWPEFrameworkAppGateway.so`
- `/usr/lib/wpeframework/plugins/libWPEFrameworkAppGateway.so`

If the `.so` is missing:
- Confirm the Step 23 configure log line includes `-DPLUGIN_APPGATEWAY=ON`.
- Check the build tree under `${BUILD_ROOT}/entservices-appgateway`.
- Ensure the install prefix is `${INSTALL_USR}` (typically `${WORKSPACE_ROOT}/install/usr`).
