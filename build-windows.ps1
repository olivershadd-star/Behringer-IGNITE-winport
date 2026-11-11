param(
    [ValidateSet("Debug", "Release")][string]$Configuration = "Release",
    [string]$SoundFont = "",
    [switch]$Diagnostics
)
$ErrorActionPreference = "Stop"
$projectRoot = $PSScriptRoot
$source = Join-Path $projectRoot "Source/Application"
$build = Join-Path $projectRoot "build/windows"
if (-not (Get-Command cmake -ErrorAction SilentlyContinue)) { throw "Installer CMake 3.20+ et Visual Studio 2022 (Developpement Desktop C++)." }
if ($SoundFont) {
    Copy-Item -LiteralPath $SoundFont -Destination (Join-Path $source "sf/Ignite.sf2")
}
$configureExtra = @()
if ($Diagnostics) { $configureExtra += '-DCMAKE_EXE_LINKER_FLAGS_RELEASE=/DEBUG' }
& cmake -S $source -B $build -G "Visual Studio 17 2022" -A x64 -DIGNITE_DESKTOP=ON -DENABLE_HARDWARE_TEST=OFF @configureExtra
if ($LASTEXITCODE -ne 0) { throw "Echec de configuration CMake" }
& cmake --build $build --config $Configuration --target Ignite --parallel 2
if ($LASTEXITCODE -ne 0) { throw "Echec de compilation" }
$binaryDir = Join-Path $build "apps/ignite/Ignite_artefacts/$Configuration"
$dist = Join-Path $projectRoot "dist/Ignite-Windows-x64"
if (Test-Path $dist) { throw "Le dossier dist existe deja. Le renommer avant de reconstruire le paquet." }
New-Item -ItemType Directory -Force $dist | Out-Null
Copy-Item (Join-Path $binaryDir "*") $dist -Recurse -Exclude '*.pdb','*.ilk','*.map'
Copy-Item (Join-Path $projectRoot "LICENSE") $dist
Copy-Item (Join-Path $projectRoot "WINDOWS-FR.md") $dist
Compress-Archive -Path (Join-Path $dist "*") -DestinationPath (Join-Path $projectRoot "dist/Ignite-Windows-x64.zip")
Write-Host "Application : $dist/Ignite.exe"
