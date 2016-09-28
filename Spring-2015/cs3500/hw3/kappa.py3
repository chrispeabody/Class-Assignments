#Chris Peabody
#5-11-2015
#file: kappa.py3

class student:
  name = "No name"
  score = 0

def foo (x):
  return int((0.02 * (x ** 3)) - (2 * (x ** 2)) + (3 * x) + 3000)

print("Hello Kappa!")

T = int(input())
roster = []

for x in range(T):
  tstudent = student()
  templine = input()
  tstudent.name = templine.split(" ")[0]
  tstudent.score = int(templine.split(" ")[1])

  roster.append(tstudent)

for x in reversed(roster):
  y = foo(x.score)
  if (y > 2000):
    print (x.name + "'s score is too large!")
  else:
    print(x.name + " " + str(y))
