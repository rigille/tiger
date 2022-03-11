mod language;

fn main() {
    let x = language::Var::Simple {
        pos: (0, 1),
        sym: String::from("haha"),
    };
    println!("Hello, world!");
}
