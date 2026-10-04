savedcmd_mindbridge.mod := printf '%s\n'   mindbridge.o | awk '!x[$$0]++ { print("./"$$0) }' > mindbridge.mod
