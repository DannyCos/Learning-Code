#[derive(Debug)]
enum State {
    State1,
    State2,
}

enum Coin {
    Penny,
    Nickel,
    Dime,
    Quarter(State),
}

fn main() {
    println!("Value of Dime is {} cents", value_in_cents(Coin::Quarter(State::State1)));
}

fn value_in_cents(coin: Coin) -> u8 {
    match coin {
	Coin::Penny => 1,
	Coin::Nickel => 5,
	Coin::Dime => 10,
	Coin::Quarter(state) => {
	    println!("State is {:?}", state);
	    25
	}
    }
}



