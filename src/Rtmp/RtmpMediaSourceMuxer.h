﻿/*
 * Copyright (c) 2016 The ZLMediaKit project authors. All Rights Reserved.
 *
 * This file is part of ZLMediaKit(https://github.com/xiongziliang/ZLMediaKit).
 *
 * Use of this source code is governed by MIT license that can be found in the
 * LICENSE file in the root of the source tree. All contributing project authors
 * may be found in the AUTHORS file in the root of the source tree.
 */

#ifndef ZLMEDIAKIT_RTMPMEDIASOURCEMUXER_H
#define ZLMEDIAKIT_RTMPMEDIASOURCEMUXER_H

#include "RtmpMuxer.h"
#include "Rtmp/RtmpMediaSource.h"

namespace mediakit {

class RtmpMediaSourceMuxer : public RtmpMuxer {
public:
    typedef std::shared_ptr<RtmpMediaSourceMuxer> Ptr;

    RtmpMediaSourceMuxer(const string &vhost,
                         const string &strApp,
                         const string &strId,
                         const TitleMeta::Ptr &title = nullptr) : RtmpMuxer(title){
        _media_src = std::make_shared<RtmpMediaSource>(vhost, strApp, strId);
        getRtmpRing()->setDelegate(_media_src);
    }
    virtual ~RtmpMediaSourceMuxer(){}

    void setListener(const std::weak_ptr<MediaSourceEvent> &listener){
        _media_src->setListener(listener);
    }

    void setTimeStamp(uint32_t stamp){
        _media_src->setTimeStamp(stamp);
    }

    int readerCount() const{
        return _media_src->readerCount();
    }

    void onAllTrackReady(){
        makeConfigPacket();
        _media_src->setMetaData(getMetadata());
    }

    // 设置TrackSource
    void setTrackSource(const std::weak_ptr<TrackSource> &track_src){
        _media_src->setTrackSource(track_src);
    }

private:
    RtmpMediaSource::Ptr _media_src;
};


}//namespace mediakit
#endif //ZLMEDIAKIT_RTMPMEDIASOURCEMUXER_H
