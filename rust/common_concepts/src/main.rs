const MAX_VALUE: u32 = 1_000_000;

fn main() {
    let x = 5;
    let mut y = 6;

    println!("x is {}", x);
    println!("y is {}", y);

    //Line below will not compile, as x is immutable by default.
    //x = 4;
    y = 5;

    println!("x is {}", x);
    println!("y is {}", y);

    //Shadowing x
    let x = "String";

    println!("x is {}", x);

    println!("MAX_VALUE is {}", MAX_VALUE);

    let guess: u32 = "42".parse().expect("Not a number!");

    //Tuple
    let tup: (i32, f64, u8) = (456, 43.54, 5);
    let (a, b, c) = tup;

    println!("Tuple contains {}, {}, {}.", a, b, c);

    let four_hundred_fifty_six = tup.0;
    let fourty_three_point_five_four = tup.1;
    let five = tup.2;

    //Arrays
    let a1 = [1, 2, 3, 4, 5];
    let a2: [i32; 5] = [1, 2, 3, 4, 5]; //array length 5 of i32.
    let a3 = [3; 5]; //5 3's. i.e. [3, 3, 3, 3, 3].

    //Index as normal
    let third = a3[2];

    //Will produce compile time error (will panic at runtime) as index out of bounds.
    let oob = a3[9];
}
