module Main (..) where

import Color
import Graphics.Element exposing (Element, container, image, middle)
import Graphics.Collage exposing (Form, collage, move, toForm, filled, circle, rect)
import Mouse
import String
import Time exposing (Time, fps, inMilliseconds)
import Window


areaW : Int
areaW =
  789


areaH : Int
areaH =
  678


maxX : Float
maxX =
  (toFloat areaW) / 2


minX : Float
minX =
  -maxX


maxY : Float
maxY =
  (toFloat areaH) / 2


minY : Float
minY =
  -maxY


{-

Notes about Creatures

verb :
  - either "standing" or "walking"

dir :
  - the first item is either "front" or "back"
  - the second item is either "left" or "right"

-}
type alias Creature =
  { x : Float
  , y : Float
  , vx : Float
  , vy : Float
  , verb : String
  , dir : ( String, String )
  }


type alias Apple =
  { x : Float
  , y : Float
  }


type alias Model =
  { creature : Creature
  , apples : List Apple
  }


initial : Model
initial =
  Model (Creature 0 0 0 0 "standing" ( "front", "left" )) []


update : Action -> Model -> Model
update action oldModel =
  case action of
    TimeDelta delta ->
      let
        target : Maybe Apple
        target =
          List.head oldModel.apples

        newCreature : Creature
        newCreature =
          oldModel.creature
            |> setVelocity target
            |> setDirection
            |> setVerb
            |> updatePosition delta target

        nextApples : List Apple
        nextApples =
          case oldModel.apples of
            a :: rest ->
              if isOverlapple newCreature a then
                rest
              else
                oldModel.apples

            [] ->
              []
      in
        { oldModel | creature = newCreature, apples = nextApples }

    MouseClick loc ->
      let
        boundX : Float
        boundX =
          clamp minX maxX loc.x

        boundY : Float
        boundY =
          clamp minY maxY loc.y

        boundLoc : { x : Float, y : Float }
        boundLoc =
          { x = boundX, y = boundY }
      in
        { oldModel | apples = List.append oldModel.apples [ boundLoc ] }


isOverlapple : Creature -> Apple -> Bool
isOverlapple c a =
  {-

    Unlike the Venomoth example, we only consider a Creature to
    overlapple an Apple if its (x, y) coordinates overlap with the
    Apple's **exactly**.

    Return True if the Apple and Creature have the same
    coordinates. Otherwise return False.

  -}
  -- TODO: Never overlapple -- DONE
  if c.x == a.x && c.y == a.y then
    True
  else
    False


calculateVelocity : Creature -> Apple -> ( Float, Float )
calculateVelocity c a =
  {-

    This function should calculate a Creature's velocity based on a
    little bit of trigonometry. Using the Creature's (x, y)
    coordinates, and the Apple's (x, y) coordinates...

    1. Figure out the angle (in radians) from the Creature to the
       Apple. The Basics.atan2 function will be helpful.

    2. Use Basics.cos and Basics.sin to get the x and y components of
       the velocity.

    3. Return the x and y velocities as a tuple. Divide each component
       by 5 to slow Quagsire down. It's not **that** fast.

  -}
  -- TODO: Zero velocity, for now. -- DONE
  let
    angle = Basics.atan2 (a.y-c.y) (a.x-c.x)
    
    xcomp = Basics.cos angle
    ycomp = Basics.sin angle
  in
    (xcomp/5, ycomp/5)


setVelocity : Maybe Apple -> Creature -> Creature
setVelocity apple creature =
  let
    -- If there's no apple, we'll default to a (0, 0) velocity.
    ( newVx, newVy ) =
      Maybe.map (calculateVelocity creature) apple
        |> Maybe.withDefault ( 0, 0 )
  in
    { creature | vx = newVx, vy = newVy }


setDirection : Creature -> Creature
setDirection c =
  {-

    This function should return a new Creature (based on the old
    Creature) that has its "dir" field set in accordance with the
    Creature's velocity.

    For the front/back status:

    - If the Creature is moving in a positive Y direction, we should
      see its back.

    - If the Creature is moving in a negative Y direction, we should
      see its front.

    - If the Creature is not moving along the Y axis, we should see
      whichever side we had seen previously (keep the old value).

    For the left/right status:

    - If the Creature is moving in a positive X direction, it should
      be facing to the right.

    - If the Creature is moving in a negative X direction, it should
      be facing to the left.

    - If the Creature is not moving along the x axis, it should be
      facing whichever side it had been facing previously (keep the
      old value).

  -}
  -- TODO: Return the same old creature, for now -- DONE
  let
    dir1 = 
      if c.vy < 0 then
        "front"
      else if c.vy > 0 then
        "back"
      else
        fst c.dir
        
    dir2 =
      if c.vx < 0 then
        "left"
      else if c.vx > 0 then
        "right"
      else
        snd c.dir
  in
    { c | dir = (dir1, dir2) }



setVerb : Creature -> Creature
setVerb c =
  {-

    This function should return a new Creature (based on the old
    Creature) that has its "verb" field set in accordance with the
    Creature's velocity.

    If the X and Y velocity of the creature are both zero, the
    Creature is standing. Otherwise it is walking.

  -}
  -- TODO: Return the same old creature, for now -- DONE
  let
    newverb =
      if c.vx == 0 && c.vy == 0 then
        "standing"
      else
        "walking"
  in
    { c | verb = newverb }


calculateNextLocation : Time -> Creature -> Apple -> ( Float, Float )
calculateNextLocation dt c a =
  {-

    This function should calculate the new location for a Creature
    based on the time elapsed since the Creature last moved, the
    current position of the Creature, its velocity, and the distance
    to the Apple. It returns the new (x, y) coordinate as a tuple of
    Floats.


    The Creature's new X coordinate can be calculated as...

        x + dt * vx

    where x is the Creature's current x position, vx is the Creature's
    current velocity in the x direction, and dt is the time since the
    Creature last moved.


    The Creature's new Y coordinate can be calculated as...

        y + dt * vy

    where y is the Creature's current y position, vy is the Creature's
    current velocity in the y direction, and dt is the time since the
    Creature last moved.


    There are a couple of exceptions to these formulas for movement...

    - If the Euclidean distance between the Creature and the Apple is
      less than 10 units, then the Creature should move directly to
      the Apple's coordinates. Use the Pythagorean Theorem.

    - If the formula produces an X value outside of [minX, maxX], the
      value should be ignored, and one of the bounds should be used
      instead. This will prevent the Creature from walking outside of
      the field. Use the Basics.clamp function for this.

    - If the formula produces an Y value outside of [minY, maxY], the
      value should be ignored, and one of the bounds should be used
      instead. This will prevent the Creature from walking outside of
      the field. Use the Basics.clamp function for this.

  -}
  -- TODO: Always move the creature to (0, 0) for now -- DONE
  let
    newX =
    if Basics.sqrt ((a.x-c.x)^2+(a.y-c.y)^2) < 10 then
      a.x
    else if c.x + dt * c.vx < minX then
      minY
    else if c.x + dt * c.vx > maxX then
      maxY
    else
      c.x + dt * c.vx
      
    newY =
    if Basics.sqrt ((a.x-c.x)^2+(a.y-c.y)^2) < 10 then
      a.y
    else if c.y + dt * c.vy < minY then
      minY
    else if c.y + dt * c.vy > maxY then
      maxY
    else
      c.y + dt * c.vy
      
  in
    (newX, newY)


updatePosition : Time -> Maybe Apple -> Creature -> Creature
updatePosition dt apple creature =
  let
    -- If there's no apple, we'll leave the Creature in its
    -- previous location
    ( newX, newY ) =
      Maybe.map (calculateNextLocation dt creature) apple
        |> Maybe.withDefault ( creature.x, creature.y )
  in
    { creature | x = newX, y = newY }



view : ( Int, Int ) -> Model -> Element
view ( w, h ) { creature, apples } =
  let
    grassForm =
      imageRoot ++ "grass.png"
        |> image areaW areaH
        |> toForm

    creatureForm =
      imagePath creature
        |> image 69 58
        |> toForm
        |> move ( creature.x, creature.y )

    forms =
      List.concat
        [ [ grassForm ]
        , List.map placeApple apples
        , [ creatureForm ]
        ]

    field =
      collage areaW areaH forms
  in
    container w h middle field


imageRoot : String
imageRoot =
  "http://cpl.mwisely.xyz/hw/10/resources/"


imagePath : Creature -> String
imagePath c =
  String.concat [ imageRoot, fst c.dir, "-", c.verb, "-", snd c.dir, ".gif" ]


placeApple : Apple -> Form
placeApple { x, y } =
  let
    appleForm =
      toForm <| image 26 26 <| imageRoot ++ "apple.png"
  in
    appleForm |> move ( x, y )


type Action
  = TimeDelta Float
  | MouseClick { x : Float, y : Float }


delta : Signal Action
delta =
  Signal.map TimeDelta (fps 30)


fieldClicks : Signal Action
fieldClicks =
  let
    relativeToField ( w, h ) ( x, y ) =
      MouseClick
        { x = (toFloat x - (toFloat w) / 2)
        , y = -(toFloat y - (toFloat h) / 2)
        }

    relativePosition =
      Signal.map2 relativeToField Window.dimensions Mouse.position
  in
    Signal.sampleOn Mouse.clicks relativePosition


input : Signal Action
input =
  Signal.merge delta fieldClicks


main : Signal Element
main =
  Signal.map2 view Window.dimensions <| Signal.foldp update initial input
