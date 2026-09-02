param(
    [string]$ReferenceFile = "$PSScriptRoot\..\reference\original_nitmod_i386.sha256",
    [string]$ModuleDirectory = "$PSScriptRoot\..\original_nitmod_shared_objects_32bit"
)

$expected = @{}
Get-Content -LiteralPath $ReferenceFile | ForEach-Object {
    if ($_ -match '^([0-9a-fA-F]{64})\s+(.+)$') {
        $expected[$matches[2].Trim()] = $matches[1].ToLowerInvariant()
    }
}

$failed = $false
foreach ($name in $expected.Keys) {
    $path = Join-Path $ModuleDirectory $name
    if (-not (Test-Path -LiteralPath $path)) {
        Write-Error "Missing reference module: $name"
        $failed = $true
        continue
    }
    $actual = (Get-FileHash -LiteralPath $path -Algorithm SHA256).Hash.ToLowerInvariant()
    if ($actual -ne $expected[$name]) {
        Write-Error "Checksum mismatch: $name"
        $failed = $true
    } else {
        Write-Host "OK $name"
    }
}

if ($failed) { exit 1 }
