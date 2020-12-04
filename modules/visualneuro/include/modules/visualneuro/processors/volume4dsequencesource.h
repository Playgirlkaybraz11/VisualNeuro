/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2015-2019 Inviwo Foundation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *********************************************************************************/

#pragma once

#include <modules/visualneuro/visualneuromoduledefine.h>
#include <modules/base/properties/basisproperty.h>
#include <modules/base/properties/volumeinformationproperty.h>
#include <inviwo/core/common/inviwo.h>
#include <inviwo/core/processors/poolprocessor.h>
#include <inviwo/core/properties/optionproperty.h>
#include <inviwo/core/properties/directoryproperty.h>
#include <inviwo/core/properties/fileproperty.h>
#include <inviwo/core/properties/buttonproperty.h>
#include <inviwo/core/ports/volumeport.h>
#include <inviwo/core/properties/stringproperty.h>

namespace inviwo {
class InviwoApplication;
class DataReaderFactory;
using Volume4DSequence = std::vector<std::shared_ptr<VolumeSequence>>;
using Volume4DSequenceOutport = DataOutport<Volume4DSequence>;

/** \docpage{org.inviwo.Volume4DSequenceSource, Volume Vector Source}
 * ![](org.inviwo.Volume4DSequenceSource.png?classIdentifier=org.inviwo.Volume4DSequenceSource)
 * Loads a sequence of 4D volumes either from a 4D dataset or from a selection of 4D datasets. The
 * filename of the source data is available via MetaData.
 *
 * ### Outport
 *   * __data__ A sequence of 4D volumes
 *
 * ### Properties
 *   * __Input type__ Select the input type, either select a single file to a 4D dataset or
 *                    use a folder
 *   * __Volume file__ If using single file mode, the file to load.
 *   * __Volume folder__ If using folder mode, the folder to look for data sets in.
 *   * __Filter__ If using folder mode, apply filter to the folder contents to find wanted
 *                data sets
 */
class IVW_MODULE_VISUALNEURO_API Volume4DSequenceSource : public PoolProcessor {
    enum class InputType { SingleFile, Folder };

public:
    virtual const ProcessorInfo getProcessorInfo() const override;
    static const ProcessorInfo processorInfo_;
    Volume4DSequenceSource(InviwoApplication* app);
    virtual ~Volume4DSequenceSource() = default;

    virtual void deserialize(Deserializer& d) override;
    virtual void process() override;

    std::string getPath() const;

private:
    std::shared_ptr<Volume4DSequence> loadFile(std::string_view path, const FileExtension& sext, DataReaderFactory* rf, pool::Progress& progress);
    std::shared_ptr<Volume4DSequence> loadFolder(std::string_view path, DataReaderFactory* rf, pool::Stop stop, pool::Progress& progress);
    void addFileNameFilters();

    DataReaderFactory* rf_;
    std::shared_ptr<Volume4DSequence> volumes_;

    Volume4DSequenceOutport outport_;

    TemplateOptionProperty<InputType> inputType_;
    FileProperty file_;
    DirectoryProperty folder_;
    StringProperty filter_;

    ButtonProperty reload_;

    BoolProperty mirrorRanges_;

    BasisProperty basis_;
    VolumeInformationProperty information_;

    bool deserialized_ = false;
};

}  // namespace inviwo
