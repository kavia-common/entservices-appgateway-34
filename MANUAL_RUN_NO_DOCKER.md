# Manual local workflow run (NO Docker / NO `act`)

This repo includes GitHub Actions workflows that are normally run with `act` (which requires Docker). If Docker is not available, you can run the same build/test steps manually on your machine.

This guide is tailored to **this checkout** (monorepo workspace containing `entservices-appgateway-34/`) and uses the bundled ZIP:
- `entservices-appgateway-34/entservices-testframework.zip`

It reproduces the **exact commands** found in:
- `entservices-appgateway-34/.github/workflows/L1-tests.yml`

## What this runs

Equivalent to the GitHub Actions job **L1-tests** (gcc + with-coverage variant) and the “Run unit tests without valgrind” step.

Notes:
- The workflow matrix includes clang and coverage variations, but the CI excludes all except `gcc + with-coverage`. This guide follows that minimal path.
- The workflow runs valgrind and coverage generation only when *not* running under `act` (`if: ${{ !env.ACT }}`). Since we are not using `act`, you *can* optionally run those steps too.

## Assumptions / prerequisites (explicit)

1. Host OS: Ubuntu 22.04 (or close). Commands use `apt` and `sudo`.
2. You have build tools: `git`, `cmake`, `ninja`, compilers installed via packages below.
3. Network access to clone:
   - `https://github.com/rdkcentral/Thunder`
   - `https://github.com/rdkcentral/ThunderTools`
   - `https://github.com/google/googletest`
   - `https://github.com/xmidt-org/trower-base64`
4. In CI, `entservices-testframework` is cloned from a private repo using a token (`RDKCM_RDKE`). Because Docker/act is unavailable, this repo provides `entservices-testframework.zip`, which we use instead.
5. This repo already contains the appgateway sources under `entservices-appgateway-34/`.

## 0) Choose a workspace directory

From the top of this monorepo:

```bash
cd /home/kavia/workspace/code-generation
```

Create a clean work directory (recommended):

```bash
mkdir -p /tmp/entservices-manual-l1
cd /tmp/entservices-manual-l1
export GITHUB_WORKSPACE="$PWD"
```

## 1) System packages (exact from workflow)

These are copied from `L1-tests.yml`:

```bash
sudo apt update && sudo apt install -y libsqlite3-dev libcurl4-openssl-dev valgrind lcov clang libsystemd-dev libboost-all-dev libwebsocketpp-dev meson libcunit1 libcunit1-dev curl protobuf-compiler-grpc libgrpc-dev libgrpc++-dev libjsoncpp-dev
```

## 2) Python dependency (exact from workflow)

```bash
python3 -m pip install --user jsonref
```

## 3) Build and install trower-base64 (exact from workflow)

```bash
if [ ! -d "trower-base64" ]; then
  git clone https://github.com/xmidt-org/trower-base64.git
fi
cd trower-base64
meson setup --warnlevel 3 --werror build
ninja -C build
sudo ninja -C build install
cd "$GITHUB_WORKSPACE"
```

## 4) Get sources: Thunder, ThunderTools, googletest

These are the same repos/refs the workflow uses.

```bash
git clone --branch R4.4.1 --depth 1 https://github.com/rdkcentral/Thunder.git Thunder
git clone --branch R4.4.3 --depth 1 https://github.com/rdkcentral/ThunderTools.git ThunderTools
git clone --branch v1.15.0 --depth 1 https://github.com/google/googletest.git googletest
```

## 5) Provide entservices-testframework from the ZIP (repo-local)

Unzip the provided framework:

```bash
unzip -q /home/kavia/workspace/code-generation/entservices-appgateway-34/entservices-testframework.zip -d "$GITHUB_WORKSPACE"
```

After unzip, you should have:

```bash
test -d "$GITHUB_WORKSPACE/entservices-testframework" && echo "OK: entservices-testframework present"
```

## 6) Provide entservices-appgateway sources into the expected path

The workflow expects `entservices-appgateway/` at `$GITHUB_WORKSPACE/entservices-appgateway`.

Use your local checkout:

```bash
cp -a /home/kavia/workspace/code-generation/entservices-appgateway-34 "$GITHUB_WORKSPACE/entservices-appgateway"
```

## 7) Patch + build ThunderTools (exact commands from workflow)

### Apply patches ThunderTools (exact)

```bash
cd "$GITHUB_WORKSPACE/ThunderTools"
patch -p1 < "$GITHUB_WORKSPACE/entservices-testframework/patches/00010-R4.4-Add-support-for-project-dir.patch"
cd "$GITHUB_WORKSPACE"
```

### Build ThunderTools (exact)

```bash
cmake -G Ninja \
  -S "$GITHUB_WORKSPACE/ThunderTools" \
  -B build/ThunderTools \
  -DEXCEPTIONS_ENABLE=ON \
  -DCMAKE_INSTALL_PREFIX="$GITHUB_WORKSPACE/install/usr" \
  -DCMAKE_MODULE_PATH="$GITHUB_WORKSPACE/install/tools/cmake" \
  -DGENERIC_CMAKE_MODULE_PATH="$GITHUB_WORKSPACE/install/tools/cmake" \
  && cmake --build build/ThunderTools -j8 \
  && cmake --install build/ThunderTools
```

## 8) Patch + build Thunder (exact commands from workflow)

### Apply patches Thunder (exact)

```bash
cd "$GITHUB_WORKSPACE/Thunder"
patch -p1 < "$GITHUB_WORKSPACE/entservices-testframework/patches/Use_Legact_Alt_Based_On_ThunderTools_R4.4.3.patch"
patch -p1 < "$GITHUB_WORKSPACE/entservices-testframework/patches/error_code_R4_4.patch"
patch -p1 < "$GITHUB_WORKSPACE/entservices-testframework/patches/1004-Add-support-for-project-dir.patch"
patch -p1 < "$GITHUB_WORKSPACE/entservices-testframework/patches/RDKEMW-733-Add-ENTOS-IDS.patch"
patch -p1 < "$GITHUB_WORKSPACE/entservices-testframework/patches/Jsonrpc_dynamic_error_handling.patch"
cd "$GITHUB_WORKSPACE"
```

### Build Thunder (exact)

```bash
cmake -G Ninja \
  -S "$GITHUB_WORKSPACE/Thunder" \
  -B build/Thunder \
  -DMESSAGING=ON \
  -DCMAKE_INSTALL_PREFIX="$GITHUB_WORKSPACE/install/usr" \
  -DCMAKE_MODULE_PATH="$GITHUB_WORKSPACE/install/tools/cmake" \
  -DGENERIC_CMAKE_MODULE_PATH="$GITHUB_WORKSPACE/install/tools/cmake" \
  -DBUILD_TYPE=Debug \
  -DBINDING=127.0.0.1 \
  -DPORT=55555 \
  -DEXCEPTIONS_ENABLE=ON \
  && cmake --build build/Thunder -j8 \
  && cmake --install build/Thunder
```

## 9) Provide entservices-apis (IMPORTANT: repo mismatch)

In CI, the workflow checks out `rdkcentral/entservices-apis` and patches it. In this monorepo, you already have `entservices-apis-34/`.

**Assumption / mapping:** use the local folder `entservices-apis-34` as `entservices-apis`:

```bash
cp -a /home/kavia/workspace/code-generation/entservices-apis-34 "$GITHUB_WORKSPACE/entservices-apis"
```

Then perform the workflow’s “Remove DTV.json” step:

```bash
rm -rf "$GITHUB_WORKSPACE/entservices-apis/jsonrpc/DTV.json"
```

Apply patches (exact):

```bash
cd "$GITHUB_WORKSPACE/entservices-apis"
patch -p1 < "$GITHUB_WORKSPACE/entservices-testframework/patches/RDKEMW-1007.patch"
cd "$GITHUB_WORKSPACE"
```

Build entservices-apis (exact):

```bash
cmake -G Ninja \
  -S "$GITHUB_WORKSPACE/entservices-apis" \
  -B build/entservices-apis \
  -DEXCEPTIONS_ENABLE=ON \
  -DCMAKE_INSTALL_PREFIX="$GITHUB_WORKSPACE/install/usr" \
  -DCMAKE_MODULE_PATH="$GITHUB_WORKSPACE/install/tools/cmake" \
  && cmake --build build/entservices-apis -j8 \
  && cmake --install build/entservices-apis
```

## 10) Generate external headers (exact)

```bash
cd "$GITHUB_WORKSPACE/entservices-testframework/Tests/" \
  && mkdir -p headers headers/network headers/proc \
  && cd headers \
  && touch rfcapi.h rbus.h pkg.h
cd "$GITHUB_WORKSPACE"
```

## 11) Toolchain selection

In CI, gcc-with-coverage toolchain is only set when `!env.ACT`. For manual runs we want the same toolchain file used by CI:

```bash
export TOOLCHAIN_FILE="$GITHUB_WORKSPACE/entservices-testframework/Tests/gcc-with-coverage.cmake"
```

## 12) Build googletest (exact)

```bash
cmake -G Ninja \
  -S "$GITHUB_WORKSPACE/googletest" \
  -B build/googletest \
  -DCMAKE_INSTALL_PREFIX="$GITHUB_WORKSPACE/install/usr" \
  -DCMAKE_MODULE_PATH="$GITHUB_WORKSPACE/install/tools/cmake" \
  -DGENERIC_CMAKE_MODULE_PATH="$GITHUB_WORKSPACE/install/tools/cmake" \
  -DBUILD_TYPE=Debug \
  -DBUILD_GMOCK=ON \
  -DBUILD_SHARED_LIBS=OFF \
  -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
  && cmake --build build/googletest -j8 \
  && cmake --install build/googletest
```

## 13) Build mocks (exact)

This is copied as-is from the workflow; it is long and includes many include paths and link wraps.

```bash
cmake \
  -S "$GITHUB_WORKSPACE/entservices-testframework/Tests/mocks" \
  -B build/mocks \
  -DBUILD_SHARED_LIBS=ON \
  -DRDK_SERVICES_L1_TEST=ON \
  -DUSE_THUNDER_R4=ON \
  -DCMAKE_TOOLCHAIN_FILE="${TOOLCHAIN_FILE}" \
  -DCMAKE_INSTALL_PREFIX="$GITHUB_WORKSPACE/install/usr" \
  -DCMAKE_MODULE_PATH="$GITHUB_WORKSPACE/install/tools/cmake" \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_CXX_FLAGS=" \
  -DEXCEPTIONS_ENABLE=ON \
  -DUSE_THUNDER_R4=ON \
  -DTHUNDER_VERSION=4 \
  -DTHUNDER_VERSION_MAJOR=4 \
  -DTHUNDER_VERSION_MINOR=4 \
  -DRDK_SERVICES_L1_TEST \
  -I $GITHUB_WORKSPACE/entservices-testframework/Tests/headers \
  -I $GITHUB_WORKSPACE/entservices-testframework/Tests \
  -I $GITHUB_WORKSPACE/entservices-appgateway/helpers \
  -I $GITHUB_WORKSPACE/Thunder/Source \
  -I $GITHUB_WORKSPACE/Thunder/Source/core \
  -I $GITHUB_WORKSPACE/install/usr/include \
  -I ./usr/include/libdrm \
  -include $GITHUB_WORKSPACE/entservices-testframework/Tests/mocks/pkg.h \
  --coverage \
  -Wall -Wno-unused-result -Wno-deprecated-declarations -Wno-error=format= \
  -Wl,-wrap,system -Wl,-wrap,popen -Wl,-wrap,syslog -Wl,-wrap,v_secure_system -Wl,-wrap,v_secure_popen -Wl,-wrap,v_secure_pclose -Wl,-wrap,unlink -Wl,-wrap,v_secure_system -Wl,-wrap,pclose -Wl,-wrap,setmntent -Wl,-wrap,getmntent" \
  && cmake --build build/mocks -j8 \
  && cmake --install build/mocks
```

## 14) Build entservices-appgateway (exact)

```bash
cmake -G Ninja \
  -S "$GITHUB_WORKSPACE/entservices-appgateway" \
  -B build/entservices-appgateway \
  -DCMAKE_INSTALL_PREFIX="$GITHUB_WORKSPACE/install/usr" \
  -DCMAKE_MODULE_PATH="$GITHUB_WORKSPACE/install/tools/cmake" \
  -DCMAKE_CXX_FLAGS=" \
  -fprofile-arcs \
  -ftest-coverage \
  -DEXCEPTIONS_ENABLE=ON \
  -DUSE_THUNDER_R4=ON \
  -DTHUNDER_VERSION=4 \
  -DTHUNDER_VERSION_MAJOR=4 \
  -DTHUNDER_VERSION_MINOR=4 \
  -DRDK_SERVICES_L1_TEST \
  -I $GITHUB_WORKSPACE/entservices-testframework/Tests/headers \
  -I $GITHUB_WORKSPACE/entservices-testframework/Tests \
  -I $GITHUB_WORKSPACE/Thunder/Source \
  -I $GITHUB_WORKSPACE/Thunder/Source/core \
  -I $GITHUB_WORKSPACE/install/usr/include \
  -I $GITHUB_WORKSPACE/install/usr/include/WPEFramework \
  -include $GITHUB_WORKSPACE/entservices-testframework/Tests/mocks/pkg.h \
  -include $GITHUB_WORKSPACE/entservices-testframework/Tests/mocks/secure_wrappermock.h \
  --coverage \
  -Wall -Wno-unused-result -Wno-deprecated-declarations -Wno-error=format= \
  -Wl,-wrap,system -Wl,-wrap,popen -Wl,-wrap,syslog -Wl,-wrap,v_secure_system -Wl,-wrap,v_secure_popen -Wl,-wrap,v_secure_pclose -Wl,-wrap,unlink \
  -DCMAKE_BUILD_TYPE=Debug \
  -DRDK_SERVICES_L1_TEST=ON \
  -DUSE_THUNDER_R4=ON \
  -DHIDE_NON_EXTERNAL_SYMBOLS=OFF \
  -DENABLE_UNIT_TESTS=ON" \
  && cmake --build build/entservices-appgateway -j8 \
  && cmake --install build/entservices-appgateway
```

## 15) Build entservices-testframework (exact)

```bash
cmake -G Ninja \
  -S "$GITHUB_WORKSPACE/entservices-testframework" \
  -B build/entservices-testframework \
  -DCMAKE_INSTALL_PREFIX="$GITHUB_WORKSPACE/install/usr" \
  -DCMAKE_MODULE_PATH="$GITHUB_WORKSPACE/install/tools/cmake" \
  -DCMAKE_CXX_FLAGS=" \
  -fprofile-arcs \
  -ftest-coverage \
  -DEXCEPTIONS_ENABLE=ON \
  -DUSE_THUNDER_R4=ON \
  -DTHUNDER_VERSION=4 \
  -DTHUNDER_VERSION_MAJOR=4 \
  -DTHUNDER_VERSION_MINOR=4 \
  -DRDK_SERVICES_L1_TEST \
  -I $GITHUB_WORKSPACE/entservices-testframework/Tests/headers \
  -I $GITHUB_WORKSPACE/entservices-appgateway/helpers \
  -I $GITHUB_WORKSPACE/entservices-testframework/Tests \
  -I $GITHUB_WORKSPACE/Thunder/Source \
  -I $GITHUB_WORKSPACE/Thunder/Source/core \
  -I $GITHUB_WORKSPACE/install/usr/include \
  -I ./usr/include/libdrm \
  -I $GITHUB_WORKSPACE/install/usr/include/WPEFramework \
  -include $GITHUB_WORKSPACE/entservices-testframework/Tests/mocks/pkg.h \
  --coverage \
  -Wall -Wno-unused-result -Wno-deprecated-declarations -Wno-error=format= \
  -Wl,-wrap,system -Wl,-wrap,popen -Wl,-wrap,syslog -Wl,--no-as-needed \
  -DCMAKE_BUILD_TYPE=Debug \
  -DRDK_SERVICES_L1_TEST=ON \
  -DUSE_THUNDER_R4=ON \
  -DHIDE_NON_EXTERNAL_SYMBOLS=OFF \
  -DENABLE_UNIT_TESTS=ON" \
  && cmake --build build/entservices-testframework -j8 \
  && cmake --install build/entservices-testframework
```

## 16) Set up filesystem fixtures (exact)

The workflow creates many dirs/files under `/opt`, `/tmp`, `/run`, `/dev`, etc. This step uses `sudo` and `mknod`.

Copied as-is:

```bash
sudo mkdir -p -m 777 \
  /tmp/test/testApp/etc/apps \
  /opt/persistent \
  /opt/secure \
  /opt/secure/reboot \
  /opt/secure/persistent \
  /opt/secure/persistent/System \
  /opt/persistent/storageManager \
  /opt/preinstall \
  /opt/logs \
  /lib/rdk \
  /run/media/sda1/logs/PreviousLogs \
  /run/sda1/UsbTestFWUpdate \
  /run/sda1/UsbProdFWUpdate \
  /run/sda2 \
  /var/run/wpa_supplicant \
  /tmp/bus/usb/devices/100-123 \
  /tmp/bus/usb/devices/101-124 \
  /tmp/block/sda/device \
  /tmp/block/sdb/device \
  /dev/disk/by-id \
  /dev \
  && \
  if [ ! -f mknod /dev/sda c 240 0 ]; then mknod /dev/sda c 240 0; fi && \
  if [ ! -f mknod /dev/sda1 c 240 0 ]; then mknod /dev/sda1 c 240 0; fi && \
  if [ ! -f mknod /dev/sda2 c 240 0 ]; then mknod /dev/sda2 c 240 0; fi && \
  if [ ! -f mknod /dev/sdb c 240 0 ]; then mknod /dev/sdb c 240 0; fi && \
  if [ ! -f mknod /dev/sdb1 c 240 0 ]; then mknod /dev/sdb1 c 240 0; fi && \
  if [ ! -f mknod /dev/sdb2 c 240 0 ]; then mknod /dev/sdb2 c 240 0; fi \
  && \
  sudo touch \
  /tmp/test/testApp/etc/apps/testApp_package.json \
  /opt/rdk_maintenance.conf \
  /opt/persistent/timeZoneDST \
  /opt/standbyReason.txt \
  /opt/tmtryoptout \
  /opt/fwdnldstatus.txt \
  /opt/dcm.properties \
  /etc/device.properties \
  /etc/dcm.properties \
  /etc/authService.conf \
  /version.txt \
  /run/media/sda1/logs/PreviousLogs/logFile.txt \
  /run/sda1/HSTP11MWR_5.11p5s1_VBN_sdy.bin \
  /run/sda1/UsbTestFWUpdate/HSTP11MWR_3.11p5s1_VBN_sdy.bin \
  /run/sda1/UsbProdFWUpdate/HSTP11MWR_4.11p5s1_VBN_sdy.bin \
  /lib/rdk/getMaintenanceStartTime.sh \
  /tmp/opkg.conf \
  /tmp/bus/usb/devices/100-123/serial \
  /tmp/bus/usb/devices/101-124/serial \
  /tmp/block/sda/device/vendor \
  /tmp/block/sda/device/model \
  /tmp/block/sdb/device/vendor \
  /tmp/block/sdb/device/model \
  && \
  sudo chmod -R 777 \
  /opt/rdk_maintenance.conf \
  /opt/persistent/timeZoneDST \
  /opt/standbyReason.txt \
  /opt/tmtryoptout \
  /opt/fwdnldstatus.txt \
  /opt/dcm.properties \
  /etc/device.properties \
  /etc/dcm.properties \
  /etc/authService.conf \
  /version.txt \
  /lib/rdk/getMaintenanceStartTime.sh \
  /tmp/opkg.conf \
  /tmp/bus/usb/devices/100-123/serial \
  /tmp/block/sda/device/vendor \
  /tmp/block/sda/device/model \
  /tmp/bus/usb/devices/101-124/serial \
  /tmp/block/sdb/device/vendor \
  /tmp/block/sdb/device/model \
  && \
  cd /dev/disk/by-id/
```

## 17) Run L1 unit tests (exact “without valgrind” step)

The workflow runs `RdkServicesL1Test` from the install prefix `install/usr/bin`.

```bash
PATH=$GITHUB_WORKSPACE/install/usr/bin:${PATH} \
LD_LIBRARY_PATH=$GITHUB_WORKSPACE/install/usr/lib:$GITHUB_WORKSPACE/install/usr/lib/wpeframework/plugins:${LD_LIBRARY_PATH} \
GTEST_OUTPUT="json:$(pwd)/rdkL1TestResults.json" \
RdkServicesL1Test && \
cp -rf $(pwd)/rdkL1TestResults.json $GITHUB_WORKSPACE/rdkL1TestResultsWithoutValgrind.json && \
rm -rf $(pwd)/rdkL1TestResults.json
```

Your results JSON will be at:

```bash
ls -l "$GITHUB_WORKSPACE/rdkL1TestResultsWithoutValgrind.json"
```

## Optional: run with valgrind (copied from workflow)

```bash
PATH=$GITHUB_WORKSPACE/install/usr/bin:${PATH} \
LD_LIBRARY_PATH=$GITHUB_WORKSPACE/install/usr/lib:$GITHUB_WORKSPACE/install/usr/lib/wpeframework/plugins:${LD_LIBRARY_PATH} \
GTEST_OUTPUT="json:$(pwd)/rdkL1TestResults.json" \
valgrind \
  --tool=memcheck \
  --log-file=valgrind_log \
  --leak-check=yes \
  --show-reachable=yes \
  --track-fds=yes \
  --fair-sched=try \
  RdkServicesL1Test && \
cp -rf $(pwd)/rdkL1TestResults.json $GITHUB_WORKSPACE/rdkL1TestResultsWithValgrind.json && \
rm -rf $(pwd)/rdkL1TestResults.json
```

## Troubleshooting tips (minimal)

- If `patch` fails: ensure the repo refs match the workflow (`Thunder R4.4.1`, `ThunderTools R4.4.3`), and that the ZIP extracted correctly to `$GITHUB_WORKSPACE/entservices-testframework`.
- If `RdkServicesL1Test` can’t find shared libs: re-check `LD_LIBRARY_PATH` includes:
  - `$GITHUB_WORKSPACE/install/usr/lib`
  - `$GITHUB_WORKSPACE/install/usr/lib/wpeframework/plugins`
- If `sudo mknod` fails (permissions/policy): you may need to skip device node setup; some tests may fail without it.

## Why this is “Docker-free”

`act` runs workflows in Docker containers. This guide runs the same build steps directly on your host OS, and uses the checked-in `entservices-testframework.zip` instead of the private `rdkcentral/entservices-testframework` checkout.
