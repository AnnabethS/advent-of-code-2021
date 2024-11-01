#[derive(Debug, PartialEq, Eq)]
pub struct GridPoint {
    pub x: i64,
    pub y: i64
}

impl GridPoint {
    pub fn new(x: i64, y: i64) -> GridPoint {
        return GridPoint { x, y };
    }
}
