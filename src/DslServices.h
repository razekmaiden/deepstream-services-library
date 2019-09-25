/*
The MIT License

Copyright (c) 2019-Present, ROBERT HOWELL

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in-
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef _DSL_DRIVER_H
#define _DSL_DRIVER_H

#include "DslPipelineBintr.h"
#include "DslSourceBintr.h"
#include "DslStreamMuxBintr.h"
#include "DslSinkBintr.h"
#include "DslOsdBintr.h"
#include "DslGieBintr.h"
#include "DslDisplayBintr.h"

typedef int DslReturnType;

namespace DSL {
    
    /**
     * @class Services
     * @brief Implements a singlton instance 
     */
    class Services
    {
    public:
    
        /** 
         * @brief Returns a pointer to this singleton
         * 
         * @return instance pointer to Services
         */
        static Services* GetServices();
        
        DslReturnType SourceNew(const std::string& source, guint type, 
            gboolean live, guint width, guint height, guint fps_n, guint fps_d);
        
        DslReturnType SourceDelete(const std::string& source);
        
        DslReturnType SinkNew(const std::string& sink, guint displayId, guint overlayId,
            guint offsetX, guint offsetY, guint width, guint height);
        
        DslReturnType SinkDelete(const std::string& sink);
        
        DslReturnType StreamMuxNew(const std::string& streammux, gboolean live, 
            guint batchSize, guint batchTimeout, guint width, guint height);
        
        DslReturnType StreamMuxDelete(const std::string& streammux);
        
        DslReturnType DisplayNew(const std::string& display, 
            guint rows, guint columns, guint width, guint height);
        
        DslReturnType DisplayDelete(const std::string& display);
        
        DslReturnType GieNew(const std::string& gie, const std::string& configFilePath, 
            guint batchSize, guint interval, guint uniqueId, guint gpuId, const 
            std::string& modelEngineFile, const std::string& rawOutputDir);
        
        DslReturnType GieDelete(const std::string& gie);
        
        DslReturnType PipelineSourceAdd(const std::string& pipeline, const std::string& source);
        
        DslReturnType PipelineSourceRemove(const std::string& pipeline, const std::string& source);
        
        DslReturnType PipelineSinkAdd(const std::string& pipeline, const std::string& sink);
        
        DslReturnType PipelineSinkRemove(const std::string& pipeline, const std::string& sink);
        
        DslReturnType PipelineStreamMuxAdd(const std::string& pipeline, const std::string& streammux);
        
        DslReturnType PipelineStreamMuxRemove(const std::string& pipeline, const std::string& streammux);

        DslReturnType PipelineOsdAdd(const std::string& pipeline, const std::string& osd);
        
        DslReturnType PipelineOsdRemove(const std::string& pipeline, const std::string& osd);
        
        DslReturnType PipelineGieAdd(const std::string& pipeline, const std::string& gie);
        
        DslReturnType PipelineGieRemove(const std::string& pipeline, const std::string& gie);
        
        DslReturnType PipelineDisplayAdd(const std::string& pipeline, const std::string& display);
        
        DslReturnType PipelineDisplayRemove(const std::string& pipeline, const std::string& display);
        
        DslReturnType PipelineNew(const std::string& pipeline);
        
        DslReturnType PipelineDelete(const std::string& pipeline);
        
        DslReturnType PipelinePause(const std::string& pipeline);
        
        DslReturnType PipelinePlay(const std::string& pipeline);
        
        DslReturnType PipelineGetState(const std::string& pipeline);
                        
        /** 
         * @brief Handles all pending events
         * 
         * @return true if all events were handled succesfully
         */
        bool HandleXWindowEvents(); 

        /**
         * @brief handle to the single main loop
        */
        GMainLoop* m_pMainLoop;
                
            
    private:

        /**
         * @brief private ctor for this singleton class
         */
        Services();

        /**
         * @brief private dtor for this singleton class
         */
        ~Services();
        
        /**
         * @brief instance pointer for this singleton class
         */
        static Services* m_pInstatnce;
        
        /**
         * @brief mutex to prevent driver reentry
        */
        GMutex m_driverMutex;

        /**
         * @brief mutex for all display critical code
        */
        GMutex m_displayMutex;
        
        /**
         * @brief handle to the X Window event thread, 
         * active for the life of the driver
        */

        /**
         * @brief a single display for the driver
        */
        Display* m_pXDisplay;
        
        GThread* m_pXWindowEventThread;
        

        std::map <std::string, std::shared_ptr<Bintr>> m_pipelines;
        
        std::map <std::string, std::shared_ptr<Bintr>> m_components;
    };  

    static gboolean MainLoopThread(gpointer arg);

    /**
     * @brief 
     * @param arg
     * @return 
     */
    static gboolean EventThread(gpointer arg);
    
    static gpointer XWindowEventThread(gpointer arg);

}


#endif // _DSL_DRIVER_H