--print("hello lua")

function DistributeEvent(EventID)
	if EventID == 1 then
		ActorID1 = CreateActor(0, 0, 0)
		AddLineTweenMove(ActorID1, 0, 0, 0, -100, 0, 400, 400, 1, true);
		AddLineTweenScale(ActorID1, 1, 1, 1, 2, 2, 2, 2, true);
		AddLineTweenRotation(ActorID1, 0, 0, 0, 0, 170, 0, 1, true);

	elseif EventID == 2 then
		ActorID2 = CreateActor(100, 0, 0)
		AddLineTweenCurve(ActorID2, 100, 0, 0, 600, 200, 100, 100, 0, 500, 500, 2, false);
		--AddLineTweenRotation(ActorID2, 0, 0, 0, 0, 170, 0, 1, false);

	elseif EventID == 3 then
		ActorID3 = CreateActor(-300, 0, 400)
		AddControl(ActorID3)
		ActorID4 = CreateActor(-300, 0, -100)
		AddLineTweenFollow(ActorID4, ActorID3, 50, 100, true);

	elseif EventID == 4 then
		ActorID5 = CreateActor(900, 0, 100)
		AddLineTweenMove(ActorID5, 900, 0, 100, 900, 0, 5000, 200, 4, true);

		ActorID6 = CreateActor(600, 0, 200)
		AddToLineTweenGroup(ActorID6)
		ActorID7 = CreateActor(800, 0, 300)
		AddToLineTweenGroup(ActorID7)
		ActorID8 = CreateActor(1000, 0, 300)
		AddToLineTweenGroup(ActorID8)
		ActorID9 = CreateActor(1200, 0, 200)
		AddToLineTweenGroup(ActorID9)

	elseif EventID == 5 then
		LineTweenGroupFollow(ActorID5, 50, 100)
	end
end
