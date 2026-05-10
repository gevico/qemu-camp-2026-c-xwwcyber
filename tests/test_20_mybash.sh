#!/bin/bash

# 此脚本由 Makefile 复制到 tests/test_20_mybash.sh，从 tests/ 目录执行
PROJECT_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
EXERCISE_DIR="$PROJECT_ROOT/exercises/20_mybash"

# 生成 mybash 命令脚本
TMPCMD=$(mktemp)
cat > "$TMPCMD" <<EOF
myfile $EXERCISE_DIR/bin/mybash
myfile $EXERCISE_DIR/obj/mybash/main.o

mysed s/unix/linux/ "unix is opensource. unix is free os."

mytrans $EXERCISE_DIR/src/mytrans/text.txt

mywc $EXERCISE_DIR/src/mytrans/text.txt
EOF

# 运行 mybash
"$EXERCISE_DIR/bin/mybash" "$TMPCMD"
EXIT_CODE=$?

rm -f "$TMPCMD"
exit $EXIT_CODE
