#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")/../exercises/20_mybash"

cmdfile=$(mktemp)
transfile=$(mktemp)
wctemp=$(mktemp)

cleanup() {
  rm -f "$cmdfile" "$transfile" "$wctemp"
}
trap cleanup EXIT

cat > "$transfile" <<'EOF'
code empowers individuals to be creators in
EOF

cat > "$wctemp" <<'EOF'
and and and and and and and and and and and the the the the the the the the the the skilled just just just
EOF

cat > "$cmdfile" <<EOF
myfile obj/myfile/myfile.o
myfile bin/mybash
mysed s/linux/linux/ "linux is opensource. unix is free os."
mytrans $transfile
mywc $wctemp
EOF

./bin/mybash "$cmdfile"
