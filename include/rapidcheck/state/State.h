#pragma once

#include <memory>

namespace rc {
namespace state {

/// Tests a stateful system. This function has assertion semantics (i.e. a
/// failure is equivalent to calling `RC_FAIL` and success is equivalent to
/// `RC_SUCCEED`) so it is intended to be used from a property.
///
/// @param initialState    The initial model state.
/// @param sut             The system under test.
/// @param generationFunc  A callable which takes the current model state as a
///                        parameter and returns a generator for a (possibly)
///                        suitable command.
template <typename State, typename Sut, typename GenFunc>
void check(const State &initialState, Sut &sut, GenFunc &&generationFunc);

/// Checks whether command is valid for the given state.
template <typename State, typename Sut>
bool isValidCommand(const Command<State, Sut> &command, const State &s0);

/// Given a type list of command types, returns a generator which randomly
/// yields generates one of them. The command will be generated by constructing
/// it either using a constructor taking the current state as as the only
/// parameter or using the default constructor if there is no such constructor.
/// Since the construction is done inside of a `gen::exec`, The command can
/// generate all of the needed values in its constructor using the
/// `Gen::operator*`. If the particular command is not valid for that state, it
/// can discard itself immediately using `RC_PRE` or `RC_DISCARD` so that
/// another one may be tried. This is intended to be used as the generator
/// function parameter of `check`
template <typename Cmd, typename... Cmds>
Gen<std::shared_ptr<const typename Cmd::CommandType>>
anyCommand(const typename Cmd::State &state);

} // namespace state
} // namespace rc

#include "State.hpp"
