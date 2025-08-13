# Testcase Summary — SCR000001 (Ignition Control)

**Release:** 1.0  
**Author:** [Your Name]  
**Date:** [YYYY-MM-DD]

---

## Overview
These testcases verify correct ON/OFF ignition control behavior and ensure that non-ignition inputs are ignored when ignition is OFF.

---

### **Case 1: Ignition ON/OFF Sequence**
- **File:** `case1_ign_on_off.csv`
- **Description:** Tests turning ignition ON, maintaining ON, then turning OFF, then ON again.
- **Expected Behavior:**
  - Engine state = 1 on ignition ON.
  - Engine speed creeps up from 0 towards idle RPM when ON and no accelerator input.
  - Engine state and speed reset to 0 when OFF.

---

### **Case 2: Rapid Toggle**
- **File:** `case2_toggle.csv`
- **Description:** Rapid ON→OFF toggling to check system responsiveness.
- **Expected Behavior:** No lag or leftover RPM after OFF.

---

### **Case 3: Noise Ignored**
- **File:** `case3_noise_ignored.csv`
- **Description:** Tests that accelerator/brake/gear inputs have no effect when ignition is OFF.
- **Expected Behavior:** Engine state remains OFF, speed = 0.

---
**Golden Outputs:**  
Each testcase has a corresponding `*_golden.csv` defining the exact expected outputs for automated comparison.
