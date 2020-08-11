use mgrep::Config;
use std::env;
use std::process;

fn main() {
    let args: Vec<String> = env::args().collect();
    let config = Config::new(&args).unwrap_or_else(|err| {
        println!("Problem parsing arguments: {}", err);
        process::exit(1);
    });

    println!("query: {}", config.query);
    println!("file: {}", config.file);

    if let Err(e) = mgrep::run(config) {
        println!("Application Error {}", e);
        process::exit(1)
    }
}
