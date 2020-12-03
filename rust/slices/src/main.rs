//Bad implementation of problem.
fn main() {
    let mut s1 = String::from("hello world");

    let word = first_word(&s1); // word will get the value 5

    s1.clear(); // this empties the String, making it equal to ""

    // word still has the value 5 here, but there's no more string that
    // we could meaningfully use the value 5 with. word is now totally

    let s2 = String::from("hello world!");

    let word1 = first_word_slice(&s2);

    println!("{}", word1);

    //s2.clear(); //Now throws compile time
}

fn first_word(s: &String) -> usize {
    let bytes = s.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return i;
        }
    }

    s.len()
}

fn first_word_slice(s: &String) -> &str {
    let bytes = s.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return &s[..i];
        }
    }

    &s[..]
}
