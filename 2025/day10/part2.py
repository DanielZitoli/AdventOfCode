from pulp import *
import re
import sys

def minPresses(buttons, voltage):
  numButtons = len(buttons)
  numDials = len(voltage)

  prob = LpProblem("buttons", LpMinimize)
  vars = []
  for i in range(numButtons):
    vars.append(LpVariable(f"button{i}", lowBound=0, cat=LpInteger))

  objective = lpSum([vars[i] for i in range(numButtons)])
  prob += objective
  
  for i in range(numDials):
    prob += (lpSum([buttons[j][i]*vars[j] for j in range(numButtons)]) == voltage[i], f"volage{i}")
  # print(prob)

  prob.solve(pulp.PULP_CBC_CMD(msg=False))
  total = 0
  for i in range(numButtons):
    total += vars[i].value()
  print(total)

  return total


def extractIntegers(input: str) -> list[int]:
    numbers = []
    number_regex = re.compile(r"-?\d+")

    for match in number_regex.finditer(input):
        numbers.append(int(match.group()))

    return numbers

def findButton(s, numDials):
  nums = extractIntegers(s)
  button = [0] * numDials
  for num in nums:
    button[num] = 1
  return button


def main():

  total = 0
  for line in sys.stdin:
    line = line.strip()
    if not line:
      continue

    inputs = line.split(' ')
    k = len(inputs)
    buttons = []

    # indicator = findIndicator(inputs[0][1:-1])
    voltages = extractIntegers(inputs[k - 1])
    numDials = len(voltages)

    for i in range(1, k - 1):
      buttons.append(findButton(inputs[i], numDials))


    # print(minPresses(indicator, buttons))
    total += minPresses(buttons, voltages)

  print(total)

  return 0


if __name__ == "__main__":
  main()
