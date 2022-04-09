use std::error::Error;
use std::fs::File;
use std::io::prelude::*;
use std::path::Path;

//const RESOLVECONF_PATH: &str  = "etc/resolve.conf";
const RESOLVECONF_PATH: &str  = "./test.txt";

fn main() {
    let path = Path::new(&RESOLVECONF_PATH);
    let display = path.display();
    let mut file = match File::open(&path) {
        Err(why) => panic!("couldn't open {}: {}", display, why),
        Ok(file) => file,
    };

    let mut s = String::new();
    match file.read_to_string(&mut s) {
        Err(why) => panic!("couldn't read {}: {}", display, why),
        Ok(_) => print!("{} countains:\n{}", display, s),
    }

}
