import argparse
import asyncio
import json
# import logging
import os
import platform
# import ssl

# from aiohttp import web

from aiortc import RTCPeerConnection, RTCSessionDescription
from aiortc.contrib.media import MediaPlayer, MediaRelay
from aiortc.rtcrtpsender import RTCRtpSender




# ===========================================================================================
# ===     This file handle RTC camera stream from raspberry pi to server and user         ===
# ===========================================================================================

ROOT = os.path.dirname(__file__)


relay = None
webcam = None

pcs = set()


async def on_shutdown():
    # close peer connections
    coros = [pc.close() for pc in pcs]
    await asyncio.gather(*coros)
    pcs.clear()

def create_local_tracks(play_from, decode):
    global relay, webcam

    if play_from:
        player = MediaPlayer(play_from, decode=decode)
        return player.audio, player.video
    else:
        options = {"framerate": "30", "video_size": "320x240", 'rtbufsize': '240M'}
        if relay is None:
            if platform.system() == "Darwin":
                webcam = MediaPlayer(
                    "default:none", format="avfoundation", options=options
                )
            elif platform.system() == "Windows":
                webcam = MediaPlayer(
                    "video=USB2.0 UVC HD Webcam", format="dshow", options=options
                )
                # webcam = MediaPlayer(
                #     "video=Integrated Camera", format="dshow", options=options
                # )
            else:
                webcam = MediaPlayer("/dev/video0", format="v4l2", options=options)
            relay = MediaRelay()
        return None, relay.subscribe(webcam.video)


def force_codec(pc, sender, forced_codec):
    kind = forced_codec.split("/")[0]
    codecs = RTCRtpSender.getCapabilities(kind).codecs
    transceiver = next(t for t in pc.getTransceivers() if t.sender == sender)
    transceiver.setCodecPreferences(
        [codec for codec in codecs if codec.mimeType == forced_codec]
    )

async def offer(hub, params):
    # print(request)
    # params = await request.json()
    # print(params)
    offer = RTCSessionDescription(sdp=params["sdp"], type=params["type"])

    pc = RTCPeerConnection()
    pcs.add(pc)

    @pc.on("connectionstatechange")
    async def on_connectionstatechange():
        print("Connection state is %s" % pc.connectionState)
        if pc.connectionState == "failed":
            await pc.close()
            pcs.discard(pc)


    await pc.setRemoteDescription(offer)

    answer = await pc.createAnswer()
    await pc.setLocalDescription(answer)
    hub.send('AnswerReqCamera', ["1", pc.localDescription.sdp, pc.localDescription.type])


    # open media source
    audio, video = create_local_tracks(
        None, decode=not (False)
    )

    if audio:
        audio_sender = pc.addTrack(audio)
        # if args.audio_codec:
        force_codec(pc, audio_sender, None)
        # elif args.play_without_decoding:
        #     raise Exception("You must specify the audio codec using --audio-codec")

    if video:
        video_sender = pc.addTrack(video)
        # if args.video_codec:
        force_codec(pc, video_sender, None)
        # elif args.play_without_decoding:
        #     raise Exception("You must specify the video codec using --video-codec")



    # return pc.localDescription.sdp, pc.localDescription.type