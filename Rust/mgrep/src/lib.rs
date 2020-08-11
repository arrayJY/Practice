#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn make_correct_config() {
        let args = vec![
            String::from("mgrep"),
            String::from("hello"),
            String::from("test.txt"),
        ];
        let correct_config = Config {
            query: String::from("hello"),
            file: String::from("test.txt"),
        };
        assert_eq!(Config::new(&args), Ok(correct_config));
    }

    #[test]
    fn make_wrong_config() {
        let args = vec![String::from("mgrep"), String::from("hello")];
        let args2 = vec![String::from("mgrep")];
        assert_eq!(Config::new(&args), Err("not enough arguments"));
        assert_eq!(Config::new(&args2), Err("not enough arguments"));
    }

    #[test]
    fn search_oneline_result() {
        let query = "three";
        let contents = "\
one two,
one two three,
one two four.";
        assert_eq!(vec!["one two three,"], search(query, contents));
    }

    #[test]
    fn search_multiline_result() {
        let query = "one";
        let contents = "\
one two,
one two three,
one two four.";
        assert_eq!(
            vec!["one two,", "one two three,", "one two four."],
            search(query, contents)
        );
    }
}

use std::error::Error;
use std::fs;

#[derive(PartialEq, Debug)]
pub struct Config {
    pub query: String,
    pub file: String,
}

impl Config {
    pub fn new(args: &[String]) -> Result<Config, &'static str> {
        if args.len() < 3 {
            return Err("not enough arguments");
        }

        let query = args[1].clone();
        let file = args[2].clone();

        Ok(Config { query, file })
    }
}

pub fn run(config: Config) -> Result<(), Box<dyn Error>> {
    let contents = fs::read_to_string(config.file)?;
    println!("Contents is: \n{}", contents);
    Ok(())
}

pub fn search<'a>(query: &str, contents: &'a str) -> Vec<&'a str> {
    let mut result = Vec::new();
    for line in contents.lines() {
        if line.contains(query) {
            result.push(line);
        }
    }
    result
}
