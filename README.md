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

```
cd $CMSSW_BASE/src/HiggsAnalysis/CombinedLimit

scramv1 b clean; scramv1 b -j$(nproc --ignore=2)
```

---
---

> [!TIP]
> Find the `.config` files in this GitHub repository<br>
> https://github.com/asimsek/CMSDijetFunctions





