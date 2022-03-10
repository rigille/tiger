pub enum Var {
  Simple { pos: Pos, sym: Symbol },
  Field { pos: Pos, var: Arc<Var>, sym: Symbol },
  Subscript { pos: Pos, var: Arc<Var>, exp: Exp },
}
// TODO replace Vec with im::Vector
pub enum Exp {
  Var { pos: Pos, var: Var },
  Nil { pos: Pos },
  Int { pos: Pos, i: i32 },
  Str { pos: Pos, s: String },
  Call { pos: Pos, func: Symbol, args: Vec<Arc<Exp>>},
  Op { pos: Pos, oper: Oper, left: Arc<Exp>, right: Arc<Exp> },
  Record { pos: Pos, typ: Symbol, fields: Vec<Field> },
  Seq { pos: Pos, seq: Vec<Arc<Exp>> },
  Assign { pos: Pos, var: Var, exp: Arc<Exp> },
  If { pos: Pos, test: Arc<Exp>, then: Arc<Exp>, elsee: Arc<Exp> },
  While { pos: Pos, test: Arc<Exp>, body: Arc<Exp> },
  For { pos: Pos, var: Symbol, lo: Arc<Exp>, hi: Arc<Exp>, body: Arc<Exp> },
  Break { pos: Pos },
  Let { pos: Pos, decs: Vec<Dec>, body: Arc<Exp> },
  Array { pos: Pos, typ: Symbol, size: Arc<Exp>, init: Arc<Exp> },
}
pub enum oper {
  plus,
  minus,
  times,
  divide,
  eq,
  neq,
  lt,
  le,
  gt,
  ge,
}
//pub enum ast {
//
//}
