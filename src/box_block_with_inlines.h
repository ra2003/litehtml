#pragma once
#include "box_model.h"
#include "box_block.h"

namespace litehtml
{
	namespace box_model
	{
		struct box_line
		{
			typedef std::vector<box_line> vector;

			int					box_left;
			int					box_right;
			int					base_line;
			int					line_height;
			litehtml::position	pos;
			box_base::vector	elements;

			box_line() : 
				pos(),
				box_left(0),
				box_right(0),
				base_line(0),
				line_height(0){}
			box_line(int left, int right, int top, int baseline, int lineheight) :
				pos(left, top, 0, lineheight),
				box_left(left),
				box_right(right),
				base_line(baseline),
				line_height(lineheight){}
			box_line(const box_line& val) :
				pos(val.pos),
				box_left(val.box_left),
				box_right(val.box_right),
				base_line(val.base_line),
				elements(val.elements),
				line_height(val.line_height) {}
			box_line(box_line&& val) :
				pos(std::move(val.pos)),
				box_left(std::move(val.box_left)),
				box_right(std::move(val.box_right)),
				base_line(std::move(val.base_line)),
				elements(std::move(val.elements)),
				line_height(std::move(val.line_height)) {}

			void add_box(const box_base::ptr& box);
			void finish(int lineheight, font_metrics& font, text_align align);
		};

		class box_block_with_inlines : public box_block
		{
			box_base::vector	m_element_boxes;
			box_line::vector	m_lines;
			text_align			m_text_align;
		public:
			box_block_with_inlines(const std::shared_ptr<element>& generated_by, const std::shared_ptr<document>& doc) :
				box_block(generated_by, doc){}

			virtual void add_box(const box_base::ptr& box) override;
			virtual void draw_children(uint_ptr hdc, int x, int y, const position* clip, draw_flag flag, int zindex) override;
			virtual void init_from_element() override;
			virtual int  calculate_base_line() const override;

		protected:
			virtual int render_children(int x, int y, int max_width, int ret_width, bool second_pass) override;

			box_line* add_line(int max_width, int line_height, font_metrics& font);
		};
	}
}