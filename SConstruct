import os
import sys
import ssl
import glob as pyglob
import shutil
import subprocess
import zipfile
import urllib.request
import urllib.error

# -- Helpers ---------------------------------------------------------------

def _fetch(url, dest, verify_ssl):
    ctx = ssl.create_default_context()
    if not verify_ssl:
        ctx.check_hostname = False
        ctx.verify_mode = ssl.CERT_NONE
    req = urllib.request.Request(url, headers={'User-Agent': 'SCons'})
    with urllib.request.urlopen(req, context=ctx) as r, open(dest, 'wb') as f:
        total = int(r.headers.get('Content-Length', 0))
        done  = 0
        while True:
            chunk = r.read(65536)
            if not chunk:
                break
            f.write(chunk)
            done += len(chunk)
            if total:
                print(f'\r  {done // 1024} / {total // 1024} KB', end='', flush=True)
    print()

def fetch(url, dest):
    for verify in (True, False):
        try:
            _fetch(url, dest, verify)
            if not verify:
                print('  Warning: SSL verification disabled (corporate proxy).')
            return
        except ssl.SSLError:
            if not verify:
                print(f'ERROR: Download failed even without SSL verification: {url}')
                Exit(1)
            print('  SSL error, retrying without verification...')
        except urllib.error.URLError as e:
            print(f'ERROR: Download failed: {e}')
            if os.path.isfile(dest):
                os.remove(dest)
            Exit(1)

# -- GCC (Windows only) ----------------------------------------------------

WINLIBS_ID = 'BrechtSanders.WinLibs.POSIX.MSVCRT'

def _find_gcc_in_winget_packages():
    base = os.path.join(os.environ.get('LOCALAPPDATA', ''), 'Microsoft', 'WinGet', 'Packages')
    if not os.path.isdir(base):
        return None
    for entry in os.listdir(base):
        if 'WinLibs' in entry or 'BrechtSanders' in entry:
            candidate = os.path.join(base, entry, 'bin', 'gcc.exe')
            if os.path.isfile(candidate):
                return os.path.join(base, entry, 'bin')
    return None

def ensure_gcc():
    if shutil.which('gcc'):
        return

    common = [
        r'C:\mingw64\bin', r'C:\mingw32\bin',
        r'C:\msys64\mingw64\bin', r'C:\msys64\ucrt64\bin',
        r'C:\msys64\mingw32\bin',
        os.path.join(os.environ.get('ProgramFiles', ''), 'mingw64', 'bin'),
    ]
    for path in common:
        if os.path.isfile(os.path.join(path, 'gcc.exe')):
            os.environ['PATH'] = path + os.pathsep + os.environ['PATH']
            print(f'Found GCC at {path}')
            return

    bin_dir = _find_gcc_in_winget_packages()
    if bin_dir:
        os.environ['PATH'] = bin_dir + os.pathsep + os.environ['PATH']
        print(f'Found GCC at {bin_dir}')
        return

    if not shutil.which('winget'):
        print('ERROR: GCC not found and winget is not available.')
        print('Install MinGW-w64 manually and add it to your PATH.')
        Exit(1)

    print(f'GCC not found. Installing via winget ({WINLIBS_ID})...')
    try:
        subprocess.run(
            ['winget', 'install', '-e', '--id', WINLIBS_ID,
             '--accept-package-agreements', '--accept-source-agreements'],
            check=True,
        )
    except subprocess.CalledProcessError:
        print('ERROR: winget install failed.')
        Exit(1)

    bin_dir = _find_gcc_in_winget_packages()
    if bin_dir:
        os.environ['PATH'] = bin_dir + os.pathsep + os.environ['PATH']
        print(f'GCC installed at {bin_dir}')
        return

    print('GCC installed. Please restart your terminal and run scons again.')
    Exit(0)

# -- CSFML -----------------------------------------------------------------

CSFML_VERSION = '2.6.0'
DEPS_DIR      = '.deps'
CSFML_ARCHIVE = f'CSFML-{CSFML_VERSION}-windows-64-bit.zip'
CSFML_FOLDER  = 'CSFML'
CSFML_URL     = (
    f'https://github.com/SFML/CSFML/releases/download/'
    f'{CSFML_VERSION}/{CSFML_ARCHIVE}'
)

def ensure_csfml():
    csfml_dir = os.path.join(DEPS_DIR, CSFML_FOLDER)
    if os.path.isdir(csfml_dir):
        return csfml_dir

    os.makedirs(DEPS_DIR, exist_ok=True)
    zip_path = os.path.join(DEPS_DIR, CSFML_ARCHIVE)

    if not os.path.isfile(zip_path):
        print(f'Downloading CSFML {CSFML_VERSION}...')
        fetch(CSFML_URL, zip_path)

    print(f'Extracting CSFML {CSFML_VERSION}...')
    with zipfile.ZipFile(zip_path) as z:
        z.extractall(DEPS_DIR)

    return csfml_dir

# -- OpenAL ----------------------------------------------------------------

OPENAL_VERSION = '1.25.1'
OPENAL_ARCHIVE = f'openal-soft-{OPENAL_VERSION}-bin.zip'
OPENAL_FOLDER  = f'openal-soft-{OPENAL_VERSION}-bin'
OPENAL_URL     = (
    f'https://github.com/kcat/openal-soft/releases/download/'
    f'{OPENAL_VERSION}/{OPENAL_ARCHIVE}'
)

def ensure_openal():
    """Download openal-soft, return (dll_path, lib_dir)."""
    openal_dir = os.path.join(DEPS_DIR, OPENAL_FOLDER)
    dll_src    = os.path.join(openal_dir, 'bin',  'Win64', 'soft_oal.dll')
    lib_dir    = os.path.join(openal_dir, 'libs', 'Win64')

    if not os.path.isfile(dll_src):
        os.makedirs(DEPS_DIR, exist_ok=True)
        zip_path = os.path.join(DEPS_DIR, OPENAL_ARCHIVE)
        if not os.path.isfile(zip_path):
            print(f'Downloading OpenAL-soft {OPENAL_VERSION}...')
            fetch(OPENAL_URL, zip_path)
        print(f'Extracting OpenAL-soft {OPENAL_VERSION}...')
        with zipfile.ZipFile(zip_path) as z:
            z.extractall(DEPS_DIR)

    return dll_src, lib_dir

# -- Environment -----------------------------------------------------------

if sys.platform == 'win32':
    ensure_gcc()

env = Environment(tools=['mingw'] if sys.platform == 'win32' else ['default'])

env.Append(
    CCFLAGS=['-std=c99', '-O3', '-march=native', '-flto'],
    LINKFLAGS=['-flto'],
    CPPPATH=['include'],
)

if sys.platform == 'win32':
    csfml_dir              = ensure_csfml()
    openal_dll, _          = ensure_openal()

    # Copy all required DLLs next to the executable
    dlls = list(pyglob.glob(os.path.join(csfml_dir, 'bin', '*.dll')))
    for src in dlls:
        dest = os.path.join('.', os.path.basename(src))
        if not os.path.isfile(dest):
            shutil.copy2(src, dest)
            print(f'Copied {os.path.basename(src)}')

    openal_dest = os.path.join('.', 'OpenAL32.dll')
    if not os.path.isfile(openal_dest):
        shutil.copy2(openal_dll, openal_dest)
        print('Copied OpenAL32.dll')

    env.Append(
        CPPPATH=[os.path.join(csfml_dir, 'include')],
        LIBPATH=[os.path.join(csfml_dir, 'lib', 'gcc')],
        LIBS=['csfml-graphics', 'csfml-audio', 'csfml-system', 'csfml-window'],
    )
else:
    # Linux / macOS: install CSFML via your package manager:
    #   apt install libcsfml-dev  /  pacman -S csfml  /  brew install csfml
    try:
        env.ParseConfig(
            'pkg-config --cflags --libs '
            'csfml-graphics csfml-audio csfml-system csfml-window'
        )
        env.Append(LIBS=['m'])
    except Exception:
        print('ERROR: CSFML not found via pkg-config.')
        print('Install it with your package manager, e.g.:')
        print('  apt install libcsfml-dev')
        print('  pacman -S csfml')
        print('  brew install csfml')
        Exit(1)

# -- Build -----------------------------------------------------------------

sources = pyglob.glob('src/**/*.c', recursive=True)
env.Program('Sand', sources)
