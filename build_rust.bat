cd rustlib
cargo build

copy "rustlib.h" "../include/rustlib.h"
copy ".\target\debug\rustlib.dll" "..\lib\"