param(
    [string]$Image = "nitmod-linux-i386"
)

$root = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path
docker info *> $null
if ($LASTEXITCODE -ne 0) {
    Write-Error "Docker Desktop's Linux container engine is not running. Start Docker Desktop and retry."
    exit $LASTEXITCODE
}

docker build --file (Join-Path $root "tools\linux-i386\Dockerfile") --tag $Image $root
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

docker run --rm --volume "${root}:/workspace" --workdir /workspace $Image
exit $LASTEXITCODE
