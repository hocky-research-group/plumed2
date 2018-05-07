/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   Copyright (c) 2011-2018 The plumed team
   (see the PEOPLE file at the root of the distribution for a list of names)

   See http://www.plumed.org for more information.

   This file is part of plumed, version 2.

   plumed is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   plumed is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with plumed.  If not, see <http://www.gnu.org/licenses/>.
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
#include "core/ActionWithValue.h"
#include "core/ActionWithArguments.h"
#include "core/ActionRegister.h"

namespace PLMD {
namespace function {

class ComposeVector:
  public ActionWithValue,
  public ActionWithArguments 
{
public:
  static void registerKeywords(Keywords&);
  explicit ComposeVector(const ActionOptions&);
  unsigned getNumberOfDerivatives() const ;
  void calculate();
  void apply();
};

PLUMED_REGISTER_ACTION(ComposeVector,"COMPOSE_VECTOR")

void ComposeVector::registerKeywords( Keywords& keys ) {
  Action::registerKeywords( keys ); ActionWithValue::registerKeywords( keys ); 
  ActionWithArguments::registerKeywords( keys ); keys.remove("NUMERICAL_DERIVATIVES"); keys.use("ARG");
}

ComposeVector::ComposeVector(const ActionOptions&ao):
Action(ao),
ActionWithValue(ao),
ActionWithArguments(ao)
{ 
  std::vector<unsigned> shape(1); shape[0]=getNumberOfArguments();
  addValue( shape ); setNotPeriodic();
}

unsigned ComposeVector::getNumberOfDerivatives() const {
  return 1;
}

void ComposeVector::calculate() {
  for(unsigned i=0;i<getNumberOfArguments();++i) getPntrToOutput(0)->set(i, getPntrToArgument(i)->get(0) );
}

void ComposeVector::apply() {

}

}
}

