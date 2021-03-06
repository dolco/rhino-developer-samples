#include "stdafx.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN SampleCaptureFrameBuffer command
//

#pragma region SampleCaptureFrameBuffer command

class CCommandSampleCaptureFrameBuffer : public CRhinoCommand
{
public:
  CCommandSampleCaptureFrameBuffer() = default;
  ~CCommandSampleCaptureFrameBuffer() = default;
  UUID CommandUUID() override
  {
    // {22292D24-C175-4CEE-B299-2BC55665014C}
    static const GUID SampleCaptureFrameBufferCommand_UUID =
    { 0x22292D24, 0xC175, 0x4CEE, { 0xB2, 0x99, 0x2B, 0xC5, 0x56, 0x65, 0x01, 0x4C } };
    return SampleCaptureFrameBufferCommand_UUID;
  }
  const wchar_t* EnglishCommandName() override { return L"SampleCaptureFrameBuffer"; }
  CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override ;
};

// The one and only CCommandSampleCaptureFrameBuffer object
static class CCommandSampleCaptureFrameBuffer theSampleCaptureFrameBufferCommand;

CRhinoCommand::result CCommandSampleCaptureFrameBuffer::RunCommand(const CRhinoCommandContext& context)
{
  UNREFERENCED_PARAMETER(context);

  CRhinoView* view = RhinoApp().ActiveView();
  if (0 == view)
    return CRhinoCommand::failure;

  CRhinoDisplayPipeline* dp = view->DisplayPipeline();
  if (0 == dp)
    return CRhinoCommand::failure;

  CRhinoDib fb;
  if (dp->CopyFrameBufferTo(fb))
  {
    ON_wString file, folder;
    CRhinoFileUtilities::GetMyDocumentsFolder(folder);
    file.Format(L"%s\\%s.png", static_cast<const wchar_t*>(folder), EnglishCommandName());
    fb.WriteToFile(file);
  }

  return CRhinoCommand::success;
}

#pragma endregion

//
// END SampleCaptureFrameBuffer command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
