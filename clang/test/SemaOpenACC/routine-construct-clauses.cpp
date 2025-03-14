// RUN: %clang_cc1 %s -fopenacc -verify

void Func();

#pragma acc routine(Func) worker
#pragma acc routine(Func) vector nohost
#pragma acc routine(Func) nohost seq
#pragma acc routine(Func) gang

// Only 1 of worker, vector, seq, gang.
// expected-error@+2{{OpenACC clause 'vector' may not appear on the same construct as a 'worker' clause on a 'routine' construct}}
// expected-note@+1{{previous clause is here}}
#pragma acc routine(Func) worker vector
// expected-error@+2{{OpenACC clause 'seq' may not appear on the same construct as a 'worker' clause on a 'routine' construct}}
// expected-note@+1{{previous clause is here}}
#pragma acc routine(Func) worker seq
// expected-error@+2{{OpenACC clause 'gang' may not appear on the same construct as a 'worker' clause on a 'routine' construct}}
// expected-note@+1{{previous clause is here}}
#pragma acc routine(Func) worker gang
// expected-error@+2{{OpenACC clause 'worker' may not appear on the same construct as a 'worker' clause on a 'routine' construct}}
// expected-note@+1{{previous clause is here}}
#pragma acc routine(Func) worker worker
// expected-error@+2{{OpenACC clause 'worker' may not appear on the same construct as a 'vector' clause on a 'routine' construct}}
// expected-note@+1{{previous clause is here}}
#pragma acc routine(Func) vector worker
// expected-error@+2{{OpenACC clause 'seq' may not appear on the same construct as a 'vector' clause on a 'routine' construct}}
// expected-note@+1{{previous clause is here}}
#pragma acc routine(Func) vector seq
// expected-error@+2{{OpenACC clause 'gang' may not appear on the same construct as a 'vector' clause on a 'routine' construct}}
// expected-note@+1{{previous clause is here}}
#pragma acc routine(Func) vector gang
// expected-error@+2{{OpenACC clause 'vector' may not appear on the same construct as a 'vector' clause on a 'routine' construct}}
// expected-note@+1{{previous clause is here}}
#pragma acc routine(Func) vector vector
// expected-error@+2{{OpenACC clause 'worker' may not appear on the same construct as a 'seq' clause on a 'routine' construct}}
// expected-note@+1{{previous clause is here}}
#pragma acc routine(Func) seq worker
// expected-error@+2{{OpenACC clause 'vector' may not appear on the same construct as a 'seq' clause on a 'routine' construct}}
// expected-note@+1{{previous clause is here}}
#pragma acc routine(Func) seq vector
// expected-error@+2{{OpenACC clause 'gang' may not appear on the same construct as a 'seq' clause on a 'routine' construct}}
// expected-note@+1{{previous clause is here}}
#pragma acc routine(Func) seq gang
// expected-error@+2{{OpenACC clause 'seq' may not appear on the same construct as a 'seq' clause on a 'routine' construct}}
// expected-note@+1{{previous clause is here}}
#pragma acc routine(Func) seq seq
// expected-error@+2{{OpenACC clause 'worker' may not appear on the same construct as a 'gang' clause on a 'routine' construct}}
// expected-note@+1{{previous clause is here}}
#pragma acc routine(Func) gang worker
// expected-error@+2{{OpenACC clause 'vector' may not appear on the same construct as a 'gang' clause on a 'routine' construct}}
// expected-note@+1{{previous clause is here}}
#pragma acc routine(Func) gang vector
// expected-error@+2{{OpenACC clause 'seq' may not appear on the same construct as a 'gang' clause on a 'routine' construct}}
// expected-note@+1{{previous clause is here}}
#pragma acc routine(Func) gang seq
// expected-error@+2{{OpenACC clause 'gang' may not appear on the same construct as a 'gang' clause on a 'routine' construct}}
// expected-note@+1{{previous clause is here}}
#pragma acc routine(Func) gang gang
// expected-error@+1{{REQUIRED}}
#pragma acc routine(Func)
// expected-error@+1{{REQUIRED}}
#pragma acc routine(Func) nohost

// only the 'dim' syntax for gang is legal.
#pragma acc routine(Func) gang(dim:1)
// expected-error@+1{{'num' argument on 'gang' clause is not permitted on a 'routine' construct}}
#pragma acc routine(Func) gang(1)
// expected-error@+1{{'num' argument on 'gang' clause is not permitted on a 'routine' construct}}
#pragma acc routine(Func) gang(num:1)
// expected-error@+1{{'static' argument on 'gang' clause is not permitted on a 'routine' construct}}
#pragma acc routine(Func) gang(static:1)
// expected-error@+2{{OpenACC 'gang' clause may have at most one 'dim' argument}}
// expected-note@+1{{previous expression is here}}
#pragma acc routine(Func) gang(dim:1, dim:2)

// worker, vector, seq don't allow arguments.
// expected-error@+1{{'num' argument on 'worker' clause is not permitted on a 'routine' construct}}
#pragma acc routine(Func) worker(1)
// expected-error@+1{{'length' argument on 'vector' clause is not permitted on a 'routine' construct}}
#pragma acc routine(Func) vector(1)
// expected-error@+1{{expected identifier}}
#pragma acc routine(Func) seq(1)

int getSomeInt();
// dim must be a constant positive integer.
// expected-error@+1{{argument to 'gang' clause dimension must be a constant expression}}
#pragma acc routine(Func) gang(dim:getSomeInt())

struct HasFuncs {
static constexpr int Neg() { return -5; }
static constexpr int Zero() { return 0; }
static constexpr int One() { return 1; }
static constexpr int Two() { return 2; }
static constexpr int Three() { return 3; }
static constexpr int Four() { return 4; }
};
// 'dim' must be 1, 2, or 3.
// expected-error@+1{{argument to 'gang' clause dimension must be 1, 2, or 3: evaluated to -5}}
#pragma acc routine(Func) gang(dim:HasFuncs::Neg())
// expected-error@+1{{argument to 'gang' clause dimension must be 1, 2, or 3: evaluated to 0}}
#pragma acc routine(Func) gang(dim:HasFuncs::Zero())
#pragma acc routine(Func) gang(dim:HasFuncs::One())
#pragma acc routine(Func) gang(dim:HasFuncs::Two())
#pragma acc routine(Func) gang(dim:HasFuncs::Three())
// expected-error@+1{{argument to 'gang' clause dimension must be 1, 2, or 3: evaluated to 4}}
#pragma acc routine(Func) gang(dim:HasFuncs::Four())

template<typename T>
struct DependentT {
// expected-error@+1{{argument to 'gang' clause dimension must be 1, 2, or 3: evaluated to -5}}
#pragma acc routine(Func) gang(dim:T::Neg())
// expected-error@+1{{argument to 'gang' clause dimension must be 1, 2, or 3: evaluated to 0}}
#pragma acc routine(Func) gang(dim:T::Zero()) nohost
#pragma acc routine(Func) nohost gang(dim:T::One())
#pragma acc routine(Func) gang(dim:T::Two())
#pragma acc routine(Func) gang(dim:T::Three())
// expected-error@+1{{argument to 'gang' clause dimension must be 1, 2, or 3: evaluated to 4}}
#pragma acc routine(Func) gang(dim:T::Four())
};

void Inst() {
  DependentT<HasFuncs> T;// expected-note{{in instantiation of}}
}
