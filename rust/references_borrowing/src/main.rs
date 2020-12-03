fn main() {
    let s1 = String::from("hello");

    let len = calculate_length(&s1); //Create reference to s1

    println!("The length of '{}' is {}.", s1, len);

    let mut s2 = s1; //s1 no longer valid
    push_world(&mut s2);
    println!("{}", s2);

    let r1 = &mut s2;
    //let r2 = &mut s2; // Only allowed one mutable reference to particular data

    let mut s3 = String::from("test");
    let r3 = &s3;
    let r4 = &s3;
    //let r5 = &mut s3;

    //println!("{}, {}, {}", r3, r4, r5);
    //With r5, causes panic. Cannot have a mutable borrow while also borrwed as immutable.

    println!("{}, {}", r3, r4); //r3 and r4 no longer used after this point.

    let r5 = &mut s3;
    println!("{}", r5);
}

fn calculate_length(s: &String) -> usize {
    //s "borrows" reference to s1.
    s.len() //Immutable by default
}

fn push_world(s: &mut String) {
    //Mutable reference allows modifying the "borrowed variable"
    s.push_str(", world");
}
