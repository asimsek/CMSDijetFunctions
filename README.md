### COMBINE Tool Setup for Dijet & Paired Dijet (Four-jet) Searches

**Skip this section if you already have the recommended COMBINE setup:**

```bash
cmsrel CMSSW_15_0_4
cd CMSSW_15_0_4/src
cmsenv

# Clone COMBINE tool
git -c advice.detachedHead=false clone --depth 1 --branch v10.5.0 \
  https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit

cd HiggsAnalysis/CombinedLimit
scramv1 b clean; scramv1 b -j$(nproc --ignore=2)
```

---

#### Pull the necessary/custom files from a different repo:

**From your new COMBINE area:**

```bash
cd $CMSSW_BASE/src/HiggsAnalysis/CombinedLimit

# Add an extra repo for the necessary files (will remove at the end)
git remote add cmsdijetfunctions https://github.com/asimsek/CMSDijetFunctions.git 2>/dev/null || true

# Validate:
git remote -v

# Set the branch
git fetch --depth 1 cmsdijetfunctions main
```

**Now define the explicit list of files you want to copy and check them out:**

```bash
# Create a minimal list for your need:
FILES=(
  'src/RooDijet*.cc'
  'src/RooModExp*.cc'
  'src/RooAtlas*.cc'
  'src/RooModDijet*.cc'
  'interface/RooDijet*.h'
  'interface/RooModExp*.h'
  'interface/RooAtlas*.h'
  'interface/RooModDijet*.h'
)

git restore --source=cmsdijetfunctions/main --worktree -- "${FILES[@]}"
```

#### Remove the newly added remote (cmsdijetfunctions) and validate:

```bash
# Remove:
git remote remove cmsdijetfunctions 2>/dev/null || true

# Validate:
git remote -v
```


---

#### Register the new classes:

**Add the following to the `src/classes_def.xml` file (just before `</lcgdict>` line):**

```xml
  <class name="RooDijetBinPdf" />
  <class name="RooDijet5ParamBinPdf" />
  <class name="RooDijet6ParamBinPdf" />
  <class name="RooDijet5ParamPolyExtBinPdf" />
  <class name="RooDijet6ParamPolyExtBinPdf" />
  <class name="RooDijet7ParamPolyExtBinPdf" />
  <class name="RooModExp3ParamBinPdf" />
  <class name="RooModExp4ParamBinPdf" />
  <class name="RooModExpBinPdf" />
  <class name="RooModExp6ParamBinPdf" />
  <class name="RooAtlas4ParamBinPdf" />
  <class name="RooAtlasBinPdf" />
  <class name="RooAtlas6ParamBinPdf" />
  <class name="RooModDijet3ParamBinPdf" />
  <class name="RooModDijet4ParamBinPdf" />
  <class name="RooModDijet5ParamBinPdf" />
  <class name="RooModDijet6ParamBinPdf" />
```


**Add the following to the `src/classes.h` file (end of the file is fine):**

```c
#include "HiggsAnalysis/CombinedLimit/interface/RooDijetBinPdf.h"
#include "HiggsAnalysis/CombinedLimit/interface/RooDijet5ParamBinPdf.h"
#include "HiggsAnalysis/CombinedLimit/interface/RooDijet6ParamBinPdf.h"
#include "HiggsAnalysis/CombinedLimit/interface/RooDijet5ParamPolyExtBinPdf.h"
#include "HiggsAnalysis/CombinedLimit/interface/RooDijet6ParamPolyExtBinPdf.h"
#include "HiggsAnalysis/CombinedLimit/interface/RooDijet7ParamPolyExtBinPdf.h"
#include "HiggsAnalysis/CombinedLimit/interface/RooModExp3ParamBinPdf.h"
#include "HiggsAnalysis/CombinedLimit/interface/RooModExp4ParamBinPdf.h"
#include "HiggsAnalysis/CombinedLimit/interface/RooModExpBinPdf.h"
#include "HiggsAnalysis/CombinedLimit/interface/RooModExp6ParamBinPdf.h"
#include "HiggsAnalysis/CombinedLimit/interface/RooAtlas4ParamBinPdf.h"
#include "HiggsAnalysis/CombinedLimit/interface/RooAtlasBinPdf.h"
#include "HiggsAnalysis/CombinedLimit/interface/RooAtlas6ParamBinPdf.h"
#include "HiggsAnalysis/CombinedLimit/interface/RooModDijet3ParamBinPdf.h"
#include "HiggsAnalysis/CombinedLimit/interface/RooModDijet4ParamBinPdf.h"
#include "HiggsAnalysis/CombinedLimit/interface/RooModDijet5ParamBinPdf.h"
#include "HiggsAnalysis/CombinedLimit/interface/RooModDijet6ParamBinPdf.h"
```

---

#### Rebuild

```bash
cd $CMSSW_BASE/src/HiggsAnalysis/CombinedLimit

scramv1 b clean; scramv1 b -j$(nproc --ignore=2)
```

---
---

> [!TIP]
> You can find the `.config` files under the `config` folder in this repository.<br>
> https://github.com/asimsek/CMSDijetFunctions


### Setup CMS Dijet Analyzer and Update `.config` Files:

```bash
cd $CMSSW_BASE/src/

git clone -b Run3_150X https://github.com/CMSDIJET/DijetRootTreeAnalyzer.git CMSDIJET/DijetRootTreeAnalyzer
cd CMSDIJET/DijetRootTreeAnalyzer
```


**Pull the `config` files:**

```bash
git remote add cmsdijetfunctions https://github.com/asimsek/CMSDijetFunctions.git 2>/dev/null || true
git remote -v
git fetch --depth 1 cmsdijetfunctions main
```


```bash
FILES=(
  'config/dijet.config'
  'config/dijet_*param.config'
  'config/dijet_Atlas*.config'
  'config/dijet_ModExp*.config'
  'config/ModDijet_*param.config'
)

git restore --source=cmsdijetfunctions/main --worktree -- "${FILES[@]}"
```


**Remove the newly added remote (cmsdijetfunctions) and validate:**

```bash
git remote remove cmsdijetfunctions 2>/dev/null || true
git remote -v
```

> [!WARNING]
> You need to update some files for the `Python 3` compatibility!


**Update `rootTools/__init__.py`**

```bash
cat > $CMSSW_BASE/src/CMSDIJET/DijetRootTreeAnalyzer/python/rootTools/__init__.py <<'EOF'
from . import RootIterator, RootFile, Utils, tdrstyle, CMS_lumi
__all__ = ["RootIterator", "RootFile", "Utils", "tdrstyle", "CMS_lumi"]
EOF
```

**Update `ramework/__init__.py`**

```bash
cat > $CMSSW_BASE/src/CMSDIJET/DijetRootTreeAnalyzer/python/framework/__init__.py <<'EOF'
import ROOT as rt

rt.gSystem.Load('$CMSSW_BASE/lib/$SCRAM_ARCH/libHiggsAnalysisCombinedLimit')
from . import Config, Drawer
__all__ = ["Config", "Drawer"]
EOF
```

**Update `python/framework/Config.py`**


```bash
sed -i 's/^import ConfigParser, os$/import configparser, os/; s/self\.config = ConfigParser\.ConfigParser()/self.config = configparser.ConfigParser()/g' python/framework/Config.py
```

**Update `python/BinnedFit.py`**

```bash
sed -i 's/^import rootTools$/from rootTools import RootIterator, Utils/; s/\<rootTools\.Utils\./Utils./g; s/\<rootTools\.RootIterator\./RootIterator./g' python/BinnedFit.py
```

**Update `python/WriteDataCard.py`**

```bash
sed -i 's/^import rootTools$/from rootTools import RootIterator, Utils/; s/\<rootTools\.Utils\./Utils./g; s/\<rootTools\.RootIterator\./RootIterator./g' python/WriteDataCard.py
```

**Update `python/GetCombine.py`**

```bash
sed -i 's/AddressOf/addressof/g; s/ProfileLikelihood/Significance/g; s/Asymptotic/AsymptoticLimits/g' python/GetCombine.py
```

**Update `python/RunCombine.py`**

```bash
sed -i \
  -e 's/combine -M Asymptotic -H ProfileLikelihood/combine -M AsymptoticLimits -d/g' \
  -e 's/combine -M MarkovChainMC -H Asymptotic/combine -M MarkovChainMC -d/g' \
  -e 's/setPhysicsModelParameterRanges/setParameterRanges/g' \
  -e 's/ProfileLikelihood/Significance/g' \
  -e 's/Asymptotic\.mH120/AsymptoticLimits.mH120/g' \
  -e 's/--minimizerTolerance/--run both --rAbsAcc 1e-5 --rRelAcc 2e-3 --cminDefaultMinimizerTolerance/g' \
  -e 's/--minimizerStrategy/--cminDefaultMinimizerStrategy/g' \
  -e "s/'python/'python3/g" \
  python/RunCombine.py
```


**Update `python/Plot1DLimit.py`**

```bash
sed -i 's/.iteritems()/.items()/g; s/xsecUL_ProfileLikelihood/xsecUL_Significance/g; s/xsecUL_Asymptotic/xsecUL_AsymptoticLimits/g' python/Plot1DLimit.py
```


**Update `python/rootTools/RootIterator.py`**

```bash
cat > $CMSSW_BASE/src/CMSDIJET/DijetRootTreeAnalyzer/python/rootTools/RootIterator.py <<'EOF'
import ROOT as rt

class RootIterator:
    def __init__(self, o):
        if hasattr(o, "Class") and o.Class().InheritsFrom("TIterator"):
            self._it = o
        elif hasattr(o, "createIterator"):
            self._it = o.createIterator()
        elif hasattr(o, "MakeIterator"):
            self._it = o.MakeIterator()
        elif hasattr(o, "componentIterator"):
            self._it = o.componentIterator()
        else:
            raise TypeError(
                f"Object of type {type(o).__name__} does not provide a ROOT iterator"
            )

    def __iter__(self):
        return self

    def __next__(self):
        n = self._it.Next()
        if not n:  # None or null pointer
            raise StopIteration
        return n

    next = __next__
EOF
```




