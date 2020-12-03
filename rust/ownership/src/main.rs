fn main() {
    let s1 = String::from("hello");
    //Different from string literal. Has pointer (to heap), length and capacity on stack.
    //Stored in heap, String type has pointer to heap

    println!("{}", s1);

    let s2 = s1;
    //Move operaiton, since s2 has copied s1 pointer (and legth, capacity). s1 no longer valid.

    //Would cause panic
    //println!("{}", s1);

    println!("{}", s2);

    //Can deep copy to copy heap data also.
    let s3 = s2.clone();

    println!("s2 = {}, s3 = {}", s2, s3);
    let s = String::from("hello"); // s comes into scope

    takes_ownership(s); // s's value moves into the function...
                        // ... and so is no longer valid here

    let x = 5; // x comes into scope

    makes_copy(x); // x would move into the function,
                   // but i32 is Copy, so it’s okay to still
                   // use x afterward
} // Here, x, s2, s3 goes out of scope, then s. But because s's value was moved, nothing
  // special happens.

fn takes_ownership(some_string: String) {
    // some_string comes into scope
    println!("{}", some_string);
} // Here, some_string goes out of scope and `drop` is called. The backing
  // memory is freed.

fn makes_copy(some_integer: i32) {
    // some_integer comes into scope
    println!("{}", some_integer);
} // Here, some_integer goes out of scope. Nothing special happens.


