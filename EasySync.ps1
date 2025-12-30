# ==========================================
#      Git 高级交互式同步脚本 (EasySync)
# ==========================================

# 设置控制台颜色函数，方便阅读
function Print-Info ($msg) { Write-Host $msg -ForegroundColor Cyan }
function Print-Ask  ($msg) { Write-Host $msg -ForegroundColor Yellow -NoNewline }
function Print-Err  ($msg) { Write-Host $msg -ForegroundColor Red }
function Print-Success ($msg) { Write-Host $msg -ForegroundColor Green }

Clear-Host
Print-Info "=== Git 自动化同步工具启动 ==="
Print-Info "当前目录: $(Get-Location)"
Write-Host ""

# ------------------------------------------------
# 1. 是否需要 Pull (拉取远程代码)
# ------------------------------------------------
Print-Ask "是否需要拉取远程代码? (Y/N) [默认N]: "
$needPull = Read-Host

if ($needPull -eq 'Y' -or $needPull -eq 'y') {
    Print-Info "`n正在拉取远程代码..."
    git pull
    if ($LASTEXITCODE -ne 0) {
        Print-Err "拉取失败！请检查是否有冲突。"
        exit
    }
} else {
    Write-Host "-> 跳过拉取步骤。" -ForegroundColor DarkGray
}

# ------------------------------------------------
# 2. 文件添加与排除逻辑 ("not 文件名" 功能)
# ------------------------------------------------
Write-Host ""
Print-Info "正在检测文件变动..."

# 先尝试添加所有文件，方便展示状态
git add . 
$status = git status -s

if ([string]::IsNullOrWhiteSpace($status)) {
    Print-Success "当前没有检测到文件变动，无需提交。"
    exit
}

# 显示将要提交的文件
Write-Host "----------------------------"
git status -s
Write-Host "----------------------------"

# 进入确认循环
while ($true) {
    Write-Host ""
    Print-Ask "以上文件将被提交，是否继续? (输入 Y 继续 / 输入 N 进行排除): "
    $confirm = Read-Host

    if ($confirm -eq 'Y' -or $confirm -eq 'y' -or $confirm -eq '') {
        # 用户确认，跳出循环
        break 
    }
    elseif ($confirm -eq 'N' -or $confirm -eq 'n') {
        # 用户选择排除文件
        Print-Ask "请输入要排除的文件 (格式: 'not 文件名', 例如 'not study1.exe'): "
        $excludeInput = Read-Host
        
        # 解析输入
        if ($excludeInput -match "^not\s+(.+)") {
            # 提取文件名
            $fileToExclude = $matches[1].Trim()
            
            # 执行 git restore --staged (把文件从暂存区移除，但不删除文件)
            git restore --staged $fileToExclude
            
            if ($?) {
                Print-Success "-> 已排除文件: $fileToExclude"
                # 再次显示状态让用户确认
                Write-Host "当前剩余暂存文件:"
                git status -s
            } else {
                Print-Err "-> 排除失败，请检查文件名是否正确。"
            }
        } else {
            Print-Err "-> 格式错误！请输入 'not 文件名' (例如: not temp.c)"
        }
    }
}

# ------------------------------------------------
# 3. 提交信息 (Commit Message)
# ------------------------------------------------
Write-Host ""
Print-Ask "请输入提交信息 (直接回车使用当前时间): "
$msgInput = Read-Host

if ([string]::IsNullOrWhiteSpace($msgInput)) {
    $dateStr = Get-Date -Format "yyyy-MM-dd HH:mm:ss"
    $commitMsg = "Auto Update: $dateStr"
} else {
    $commitMsg = $msgInput
}

Print-Info "`n正在提交..."
git commit -m "$commitMsg"

# ------------------------------------------------
# 4. 推送到远程 (Push)
# ------------------------------------------------
Print-Info "正在推送到远程仓库..."
git push

if ($LASTEXITCODE -eq 0) {
    Write-Host ""
    Print-Success "============================="
    Print-Success "   恭喜！同步成功 (Success)   "
    Print-Success "============================="
} else {
    Write-Host ""
    Print-Err "============================="
    Print-Err "   同步失败 (Failed)          "
    Print-Err "============================="
    Print-Err "可能原因: 网络问题 或 远程有更新未拉取"
}

# 脚本结束，Bat文件会负责暂停