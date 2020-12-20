struct User {
    username: String,
    email: String,
    sign_in_count: u64,
    active: bool,
}

//Tuple structs
struct Colour(u32, u32, u32);
struct Point(i32, i32);

fn main() {
    let mut user1 = User {
        username: String::from("User 1"),
        email: String::from("user1@fake.com"),
        sign_in_count: 1,
        active: true,
    };

    user1.active = false;

    let user2 = construct_user(String::from("User 2"), String::from("user2@fake.com"));

    //create instance of user using params from existing user

    let mut user2 = User {
        username: String::from("User 3"),
        email: String::from("user3@fake.com"),
        ..user1
    };

    let rgb = Colour(255, 255, 255);
    let point = Point(3, 4);

    struct_example();
}

fn construct_user(username: String, email: String) -> User {
    User {
        username,
        email,
        sign_in_count: 1,
        active: false,
    }
}

//*Example of using structs to find the area of a rectangle

//opt in to debug
#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}

//Implement methods for Rectangle
impl Rectangle {
    fn area(&self) -> u32 {
        self.width * self.height
    }
    fn can_hold(&self, rect: &Rectangle) -> bool {
        self.width > rect.width && self.height > rect.height
    }
}

//Can have multiple impl blocks
impl Rectangle {
    fn square(size: u32) -> Rectangle {
	Rectangle {
	    width: size,
	    height: size,
	}
    }
}

fn struct_example() {
    let rect = Rectangle {
        width: 32,
        height: 40,
    };

    //Print rectangle using seperate function
    println!("Area of the rectangle is {}", area(&rect));

    //Debug print rectangle
    println!("Rectangle is {:?} \n{:#?}", rect, rect);

    //Print rectangle using implemented function
    println!("Area of rectangle is {}", rect.area());

    let rect2 = Rectangle {
        width: 16,
        height: 30,
    };

    println!("Can rect hold rect2? {}", rect.can_hold(&rect2));
    println!("Can rect2 hold rect? {}", rect2.can_hold(&rect));

    //Associated functions are called with the :: operator
    let rect3 = Rectangle::square(16);

    println!("Area of rect3 is {}", rect3.area());
}

fn area(rectangle: &Rectangle) -> u32 {
    rectangle.width * rectangle.height
}
