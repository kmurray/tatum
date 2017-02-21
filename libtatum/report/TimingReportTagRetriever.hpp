#ifndef TATUM_TIMING_REPORT_TAG_RETRIEVER_HPP
#define TATUM_TIMING_REPORT_TAG_RETRIEVER_HPP

namespace tatum { namespace detail {

    //An abstract interface for retrieving tag information
    //
    //This is useful for reporting routings which can work for either setup or hold
    class TagRetriever {
        public:
            virtual ~TagRetriever() = default;

            virtual TimingTags::tag_range tags(NodeId node, TagType tag_type) const = 0;
            virtual TimingTags::tag_range slacks(NodeId node) const = 0;
            virtual TimingPathType type() const = 0;
    };

    class SetupTagRetriever : public TagRetriever {
        public:
            SetupTagRetriever(const SetupTimingAnalyzer& analyzer): analyzer_(analyzer) {}

            TimingTags::tag_range tags(NodeId node, TagType tag_type) const override {
                return analyzer_.setup_tags(node, tag_type);           
            }

            TimingTags::tag_range slacks(NodeId node) const override {
                return analyzer_.setup_slacks(node);           
            }

            TimingPathType type() const override {
                return TimingPathType::SETUP;
            }
        private:
            const SetupTimingAnalyzer& analyzer_;
    };

    class HoldTagRetriever : public TagRetriever {
        public:
            HoldTagRetriever(const HoldTimingAnalyzer& analyzer): analyzer_(analyzer) {}

            TimingTags::tag_range tags(NodeId node, TagType tag_type) const override {
                return analyzer_.hold_tags(node, tag_type);           
            }

            TimingTags::tag_range slacks(NodeId node) const override {
                return analyzer_.hold_slacks(node);           
            }

            TimingPathType type() const override {
                return TimingPathType::HOLD;
            }
        private:
            const HoldTimingAnalyzer& analyzer_;
    };

}} //namespace

#endif
