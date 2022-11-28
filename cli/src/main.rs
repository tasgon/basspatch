use std::{env, io::Write, process::Command};

const LIBRARY: &'static [u8] = include_bytes!("../../basspatch.so");
const TEMP_PATH: &'static str = "/tmp/basspatch.so";

fn main() -> std::io::Result<()> {
    let target = env::args().last().unwrap();
    std::fs::File::create(TEMP_PATH)?.write(LIBRARY)?;
    ctrlc::set_handler(move || {});
    env::set_var("LD_PRELOAD", TEMP_PATH);
    if let Err(e) = Command::new(&target).status() {
        eprintln!("[basspatch] Error running {target}:\n\t{e}");
    }

    println!("[basspatch] Cleaning up...");
    std::fs::remove_file(TEMP_PATH);

    Ok(())
}
