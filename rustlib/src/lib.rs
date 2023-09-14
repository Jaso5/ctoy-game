static mut CTX: LibCtx = LibCtx {
    i: 0
};

struct LibCtx {
    i: u32
}

#[no_mangle]
pub unsafe extern "C" fn incr() -> u32 {
    CTX.i += 1;

    return CTX.i;
}

